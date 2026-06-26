# Mini Search Engine

A modular search engine built in Modern C++17.

## Features

- Load text documents from a folder
- Tokenize document contents
- Build an inverted index
- Fast word lookup using `std::unordered_map`
- Modular object-oriented design

## Technologies

- C++17
- STL
- std::filesystem
- std::unordered_map
- std::vector
- Git & GitHub

## Project Structure

```
Mini_SearchEngine/
│
├── data/
├── include/
│   ├── Document.h
│   ├── DocumentLoader.h
│   ├── Tokenizer.h
│   └── InvertedIndex.h
│
├── src/
│   ├── Document.cpp
│   ├── DocumentLoader.cpp
│   ├── Tokenizer.cpp
│   ├── InvertedIndex.cpp
│   └── main.cpp
```

## Current Features

- Document Loading
- Tokenization
- Inverted Index

## Future Improvements

- Interactive Search
- Case-insensitive Search
- Punctuation Removal
- TF-IDF Ranking
- Boolean Search
- Trie-based Autocomplete
- CMake Build System


## Author
Dibyaranjan Sahoo