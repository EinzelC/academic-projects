import json
from pathlib import Path

data_folder = Path(__file__).parent
filename = data_folder / "grades.txt"
if not filename.exists():
    filename = data_folder / "grades-1.txt"

grades = {}

if filename.exists():
    with filename.open("r") as file:
        grades = json.load(file)


def save_grades():
    with filename.open("w") as file:
        json.dump(grades, file, indent=4)


def get_grade():
    while True:
        try:
            return float(input("Enter the grade: "))
        except ValueError:
            print("Invalid grade. Please enter a number.")


def find_student(name):
    normalized_name = " ".join(name.split()).casefold()
    for student_name in grades:
        if student_name.casefold() == normalized_name:
            return student_name
    return None


while True:
    print("\n=== Grades Menu ===")
    print("1. Add a student")
    print("2. View a grade")
    print("3. Edit a grade")
    print("4. Delete a student")
    print("5. Exit")

    choice = input("Enter your choice (1-5): ")

    if choice == '1':
        name = input("Enter the student's full name: ").strip()
        grades[name] = get_grade()
        save_grades()
        print(f"Grade saved for {name}.")

    elif choice == '2':
        name = find_student(input("Enter the student's full name: "))
        if name is not None:
            print(f"{name}'s grade is {grades[name]}.")
        else:
            print("No grade found for that student.")

    elif choice == '3':
        name = find_student(input("Enter the student's full name: "))
        if name is not None:
            grades[name] = get_grade()
            save_grades()
            print(f"Grade updated for {name}.")
        else:
            print("No grade found for that student.")

    elif choice == '4':
        name = find_student(input("Enter the student's full name: "))
        if name is not None:
            del grades[name]
            save_grades()
            print(f"Grade deleted for {name}.")
        else:
            print("No grade found for that student.")

    elif choice == '5':
        print("Exiting program. Goodbye!")
        break

    else:
        print("Invalid choice. Please enter a number between 1 and 5.")