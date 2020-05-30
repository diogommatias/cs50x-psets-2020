from sys import argv, exit
import cs50
import csv

# exit if input is incorrect
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# open csv file that contains student's info for reading
with open(argv[1], "r") as students:

    # create DictReader
    reader = csv.DictReader(students)

    # open the database
    db = cs50.SQL("sqlite:///students.db")

    for row in reader:

        # split the name
        full_name = row["name"].split()

        # insert into the database
        if len(full_name) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                       full_name[0], full_name[1], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       full_name[0], full_name[1], full_name[2], row["house"], row["birth"])