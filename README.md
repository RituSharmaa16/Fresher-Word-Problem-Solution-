# Fresher-Word-Problem-Solution-
**Global Variables:**
wordSet holds all words (using an unordered_set for O(1) lookups).
wordQueue is a queue of pairs (each pair represents a WordPart with first as the original word and second as the remaining part).

**getPrefixes Function:**
Iterates character by character through a word, building a prefix.
If the prefix exists in wordSet, it is added to the list of valid prefixes.

**addWordsFromFile Function:**
Reads each line from the file, trims it, and adds the word to wordSet.
For each word, it computes its valid prefixes and enqueues a pair (word, remainder) where the remainder is the word after removing the prefix.

**findLongestCompoundWords Function:**
Processes each pair from the queue.
If the remainder is a valid word, it considers the original word as a compound candidate.
Otherwise, it splits the remainder further using its valid prefixes and enqueues new pairs.
Tracks the longest and second longest compound words found.

**Main Function:**
Measures execution time, calls the functions, and prints the results in the required format.
