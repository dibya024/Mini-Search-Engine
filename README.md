# Mini Search Engine

A modular **C++ search engine built from scratch** using an **Inverted Index, TF-IDF relevance ranking, Boolean query processing, and Positional Indexing** for efficient document retrieval.

## Features

- Efficient keyword retrieval using an **Inverted Index**
- Single-word and multi-word **AND search**
- Boolean **OR search**
- **TF-IDF relevance ranking** for search results
- **Exact phrase search** using a Positional Inverted Index
- Hash-based query optimization using `std::unordered_map` and `std::unordered_set`
- Modular Object-Oriented C++ architecture
- CMake-based build system

## How It Works

```text
Documents
    ↓
DocumentLoader
    ↓
Tokenizer
    ↓
Positional Inverted Index
    ↓
QueryProcessor
    ↓
Boolean / Phrase Retrieval
    ↓
Search Results
```

The inverted index maps terms to document postings containing term frequencies and word positions. Positional information enables exact phrase matching, while TF-IDF scores are used to rank relevant search results.

## TF-IDF Ranking

Matching documents are ranked using TF-IDF relevance scoring:

```text
TF-IDF = Term Frequency × Inverse Document Frequency
```

Higher-scoring documents are displayed first based on their relevance to the query.

## Performance Optimization

Document intersection was optimized using hash-based lookup with `std::unordered_set`, improving average query intersection complexity from:

```text
O(n × m) → O(n + m)
```

## Project Structure

```text
Mini_SearchEngine/
├── include/
│   ├── Document.h
│   ├── DocumentLoader.h
│   ├── Tokenizer.h
│   ├── InvertedIndex.h
│   ├── QueryProcessor.h
│   └── Ranker.h
├── src/
│   ├── main.cpp
│   ├── Document.cpp
│   ├── DocumentLoader.cpp
│   ├── Tokenizer.cpp
│   ├── InvertedIndex.cpp
│   ├── QueryProcessor.cpp
│   └── Ranker.cpp
├── data/
├── CMakeLists.txt
└── README.md
```

## Build and Run

### Requirements

- C++17
- CMake
- GCC / MinGW or another C++17-compatible compiler

### Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Run from the project root:

```bash
./build/SearchEngine
```

On Windows:

```powershell
.\build\SearchEngine.exe
```

## Tech Stack

**C++17 · STL · CMake · Git**

**Concepts:** Inverted Index, Positional Indexing, TF-IDF, Boolean Retrieval, Hash Tables, Information Retrieval, OOP

## Future Improvements

- Boolean NOT queries and operator precedence
- Stop-word removal and stemming
- Trie-based autocomplete and search suggestions
- Persistent index storage
- Performance benchmarking on larger document collections

## Author

**Dibyaranjan Sahoo**

[GitHub](https://github.com/dibya024)