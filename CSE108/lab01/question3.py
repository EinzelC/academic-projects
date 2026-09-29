from pathlib import Path

search_word = input("Enter a word to search for: ")
clean_word = search_word.strip().lower()

summary_file = Path(__file__).parent / "PythonSummary.txt"
with summary_file.open("r") as file:
    content = file.read().lower()

word_count = content.count(clean_word)
print(f"The word '{search_word}' occurs {word_count} times.")