from sys import argv, exit
import csv

STRs = []

# checks if the input is correct
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open the csv file
with open(argv[1], 'r', newline='') as csv_file:
    # transforms each row from the csv file to a dictionary
    database = csv.DictReader(csv_file)
    fieldnames = database.fieldnames

    # open the dna sequence file
    with open(argv[2], 'r') as file:
        sequence = file.readline()

        # searches for the specific STRs on the csv file in the dna sequence file
        for i in range(1, len(fieldnames)):
            counter = 0     # helps strike
            strike = 0      # records the highest strike lenght of a STR in the dna sequence
            j = 0
            while j < len(sequence):
                if sequence[j: j + len(fieldnames[i])] == fieldnames[i]:
                    counter += 1
                    j += len(fieldnames[i])
                else:
                    counter = 0
                    j += 1
                if counter > strike:
                    strike = counter

            STRs.append(strike)

    # searches the name of person which corresponds to the STRs array on the database
    for row in database:
        found = True
        for i in range(1, len(fieldnames)):
            if int(row.get(fieldnames[i])) != STRs[i - 1]:
                found = False
                break
        if found:
            print(row['name'])
            break
    # prints this if no one is found on the database
    if not found:
        print("No match")
