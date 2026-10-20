from flask import Flask, jsonify, request, render_template

app = Flask(__name__)

# In-memory "database" to store students and grades
# (Note: Data will reset if you restart the Flask server)
grades_db = {
    "Yenz Dexul": 92.1,
    "Locke Hartford": 88.5,
    "Kishuu Satus": 95.0
}

# frontend route
@app.route('/')
def index():
    # Serves the main HTML page from the 'templates' folder
    return render_template('index.html')

# rest api routes

# get all students
@app.route('/grades', methods=['GET'])
def get_all_grades():
    # Convert the dictionary into a list of JSON objects for the frontend
    students = [{"name": name, "grade": grade} for name, grade in grades_db.items()]
    return jsonify(students)

# get specific student
@app.route('/grades/<student_name>', methods=['GET'])
def get_grade(student_name):
    if student_name in grades_db:
        return jsonify({"name": student_name, "grade": grades_db[student_name]})
    return jsonify({"error": "Student not found"}), 404

# create new student
@app.route('/grades', methods=['POST'])
def create_student():
    data = request.get_json()
    name = data.get('name')
    grade = data.get('grade')
    
    if not name or grade is None:
        return jsonify({"error": "Missing name or grade"}), 400
        
    grades_db[name] = float(grade)
    return jsonify({"name": name, "grade": grades_db[name]}), 201

# edit gratde with PUT method
@app.route('/grades/<student_name>', methods=['PUT'])
def update_grade(student_name):
    data = request.get_json()
    grade = data.get('grade')
    
    if student_name not in grades_db:
        return jsonify({"error": "Student not found"}), 404
        
    grades_db[student_name] = float(grade)
    return jsonify({"name": student_name, "grade": grades_db[student_name]})

# DELETE student
@app.route('/grades/<student_name>', methods=['DELETE'])
def delete_student(student_name):
    if student_name not in grades_db:
        return jsonify({"error": "Student not found"}), 404
        
    deleted_grade = grades_db.pop(student_name)
    return jsonify({"name": student_name, "grade": deleted_grade})

if __name__ == '__main__':
    # Run the app in debug mode on localhost:5000
    app.run(debug=True)