
from pathlib import Path


class Course:
    def __init__(self, dept, number, name, credits, days, start_time, end_time, avg_grade):
        self.dept = dept
        self.number = number
        self.name = name
        self.credits = credits
        self.days = days
        self.start_time = start_time
        self.end_time = end_time
        self.avg_grade = avg_grade

    def format_schedule(self, course_index):
        return (
            f"COURSE {course_index}: {self.dept}{self.number}: {self.name}\n"
            f"Number of Credits: {self.credits}\n"
            f"Days of Lectures: {self.days}\n"
            f"Lecture Time: {self.start_time} - {self.end_time}\n"
            f"Stat: on average, students get {self.avg_grade}% in this course"
        )


input_file = Path(__file__).parent / "classesInput-1.txt"
output_file = Path(__file__).parent / "classSchedule.txt"
schedules = []

with input_file.open("r") as file:
    num_courses = int(file.readline().strip())

    for course_index in range(1, num_courses + 1):
        dept = file.readline().strip()
        number = file.readline().strip()
        name = file.readline().strip()
        credits = file.readline().strip()
        days = file.readline().strip()
        start_time = file.readline().strip()
        end_time = file.readline().strip()
        avg_grade = file.readline().strip()

        course = Course(
            dept, number, name, credits, days, start_time, end_time, avg_grade
        )
        schedules.append(course.format_schedule(course_index))

schedule_text = "\n\n".join(schedules)
output_file.write_text(schedule_text + "\n")
print(schedule_text)