user_input = input("Enter two or more numbers separated by spaces: ")

listofnumbers = user_input.split()

print("You entered: ", len(listofnumbers), " numbers.")

if (len(listofnumbers) < 2):
    print("Please enter at least two numbers.")
    exit()

sum = 0.0

for number in listofnumbers:
    try:
        float_number = float(number)
        sum += float_number
        
    except ValueError:
        print("Invalid input:", number, "is not a number.")

print("The sum of the numbers is:", sum)