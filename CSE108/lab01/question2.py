sentence = input("Enter a sentence: ")
repeat_amount = int(input("Enter the number of times to repeat the sentence: "))

with open("CompletedPunishment.txt", "w") as file:
    for i in range(repeat_amount):
        file.write(sentence + "\n")

print("Done writing to file")