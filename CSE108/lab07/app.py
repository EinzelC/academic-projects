from flask import Flask, jsonify, request, render_template
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column
from sqlalchemy import String, Float
from math import isfinite
from sqlalchemy.exc import SQLAlchemyError


# SETUP & CONFIGURATION 

class Base(DeclarativeBase):
    pass

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///grades.db"
db = SQLAlchemy(app, model_class=Base)


# DATABASE MODEL 

class Student(db.Model):
    # Using the modern 2.0 syntax with type hints
    name: Mapped[str] = mapped_column(String(120), primary_key=True)
    grade: Mapped[float] = mapped_column(Float, nullable=False)

    def to_dict(self):
        return {"name": self.name, "grade": self.grade}

# Create tables on startup
with app.app_context():
    db.create_all()


# HELPER FUNCTION 

def valid_record(data, needs_name=False):
    if not isinstance(data, dict):
        return False
    if needs_name:
        name = data.get("name")
        if not isinstance(name, str) or not name.strip():
            return False
    grade = data.get("grade")
    return type(grade) in (int, float) and isfinite(grade)


# ROUTES


# Serve Frontend
@app.route('/')
def index():
    return render_template('index.html')

# READ ALL 
@app.get("/grades")
def list_grades():
    students = db.session.execute(
        db.select(Student).order_by(Student.name)
    ).scalars().all()
    return jsonify({s.name: s.grade for s in students})

# READ ONE 
@app.get("/grades/<name>")
def get_grade(name):
    # db.session.get uses the primary key
    student = db.session.get(Student, name)
    if student is None:
        return jsonify(error="Not found"), 404
    return jsonify(student.to_dict())

# CREATE 
@app.post("/grades")
def create_grade():
    data = request.get_json(silent=True)
    if not valid_record(data, needs_name=True):
        return jsonify(error="Invalid input"), 400
    
    name = data["name"].strip()
    if db.session.get(Student, name) is not None:
        return jsonify(error="Already exists"), 409
        
    try:
        student = Student(name=name, grade=data["grade"])
        db.session.add(student)
        db.session.commit()
        return jsonify(student.to_dict()), 201
    except SQLAlchemyError:
        db.session.rollback()
        app.logger.exception("Database write failed")
        return jsonify(error="Database error"), 500

# UPDATE 
@app.put("/grades/<name>")
def edit_grade(name):
    student = db.session.get(Student, name)
    if student is None:
        return jsonify(error="Not found"), 404
        
    data = request.get_json(silent=True)
    if not valid_record(data):
        return jsonify(error="Invalid input"), 400
        
    try:
        student.grade = data["grade"]
        db.session.commit()
        return jsonify(student.to_dict())
    except SQLAlchemyError:
        db.session.rollback()
        app.logger.exception("Database write failed")
        return jsonify(error="Database error"), 500

# DELETE 
@app.delete("/grades/<name>")
def delete_grade(name):
    student = db.session.get(Student, name)
    if student is None:
        return jsonify(error="Not found"), 404
        
    try:
        db.session.delete(student)
        db.session.commit()
        return jsonify(deleted=name)
    except SQLAlchemyError:
        db.session.rollback()
        app.logger.exception("Database write failed")
        return jsonify(error="Database error"), 500

if __name__ == '__main__':
    app.run(debug=True)