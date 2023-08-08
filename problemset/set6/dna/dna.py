import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dna.py data.csv sequence.txt')
        return 0
    # TODO: Read database file into a variable
    database = open(sys.argv[1], 'r')
    reader = csv.reader(database)
    datadic = dict()
    strlist = []
    for row in reader:
        if row[0] == 'name':
            strlist = row[1:]
        else:
            datadic[row[0]] = row[1:]
    database.close()
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as f:
        sequence_data = csv.reader(f)
        for seq in sequence_data:
            sequence = seq[0]
    # TODO: Find longest match of each STR in DNA sequence
    match_number = [str(longest_match(sequence, strmark)) for strmark in strlist]
    # TODO: Check database for matching profiles
    for name in datadic:
        if datadic[name] == match_number:
            print(name)
            return 1
    print('No match')
    return 1


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
