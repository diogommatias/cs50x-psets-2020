from sys import argv, exit
import cs50

# exit if input is incorrect
if len(argv) != 2:
    print("Usage: python roster.py <house_name>")
    exit(1)

# open the database
db = cs50.SQL("sqlite:///students.db")

# query of the students of a specific house ordered by the student last name, or first name if equal
students = db.execute("SELECT * FROM students WHERE house LIKE ? ORDER BY last ASC, first ASC", argv[1])

# print the students
for row in students:

    if row["middle"] == None:
        print("{} {}, born {}".format(row["first"], row["last"], row["birth"]))
    else:
        print("{} {} {}, born {}".format(row["first"], row["middle"], row["last"], row["birth"]))