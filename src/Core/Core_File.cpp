#include <filesystem>
#include <iostream>
#include <fstream>

#include "Core.h"

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

void Core::saveToFile() {
    std::filesystem::path dataPath("data");
    auto localDefinitionsPath = dataPath / "local" / dataSpecifier / "data.txt";

    std::filesystem::create_directories(localDefinitionsPath.parent_path());
    std::ofstream dataOutput(localDefinitionsPath);

    if (dataOutput.is_open()) {
        for (Word* word : wordCollection) {
            if (unlikely(word == nullptr)) {
                std::cout << "[WARN] An item in the word collection was null.\n";
                continue;
            }

            if (unlikely(word->isDeleted())) {
                continue;
            }

            for (Definition* def : word->defs) {
                if (unlikely(def == nullptr)) {
                    std::cout << "[WARN] An item in the word " << word->orginalString << "'s definition was null.\n";
                    continue;
                }

                if (unlikely(def->isDeleted())) {
                    continue;
                }

                dataOutput << word->orginalString << "\t" << def->originalString << "\n";
            }
        }

        dataOutput.close();
        std::cout << "[INFO] Wrote words and definitions to " << dataPath << "\n";
    } else {
        std::cout << "[ERROR] Could not open " << dataPath << " for writing.\n";
    }

    auto favoritesPath = dataPath / "favorite" / dataSpecifier / "data.txt";
    std::filesystem::create_directories(favoritesPath.parent_path());
    std::ofstream favoritesOutput(favoritesPath);

    if (favoritesOutput.is_open()) {
        for (Word* word : wordCollection) {
            if (unlikely(word == nullptr)) {
                std::cout << "[WARN] An item in the word collection was null.\n";
                continue;
            }

            if (unlikely(word->isDeleted()) || likely(!word->IsFavorite)) {
                continue;
            }

            favoritesOutput << word->orginalString << "\n";
        }

        favoritesOutput.close();
        std::cout << "[INFO] Wrote favorite words to " << favoritesPath << "\n";
    } else {
        std::cout << "[ERROR] Could not open " << favoritesPath << " for writing.\n";
    }

    // auto historyPath = dataPath / "history" / dataSpecifier / "data.txt";
    // std::filesystem::create_directories(historyPath.parent_path());
    // std::ofstream historyOutput(historyPath);

    // if (historyOutput.is_open()) {
    //     for (Word* word : mHistory) {
    //         if (unlikely(word == nullptr)) {
    //             std::cout << "[WARN] An item in the history was null.\n";
    //             continue;
    //         }

    //         if (unlikely(word->isDeleted())) {
    //             continue;
    //         }

    //         historyOutput << word->orginalString << "\n";
    //     }

    //     historyOutput.close();
    //     std::cout << "[INFO] Wrote history to " << historyPath << "\n";
    // } else {
    //     std::cout << "[ERROR] Could not open " << historyPath << "for writing.\n";
    // }
}

void Core::loadFromFile() {
    std::filesystem::path dataPath("data");
    auto localDefinitionsPath = dataPath / "local" / dataSpecifier / "data.txt";
    auto favoritesPath = dataPath / "favorite" / dataSpecifier / "data.txt";
    auto historyPath = dataPath / "history" / dataSpecifier / "data.txt";

    std::ifstream localDefinitionsFile(localDefinitionsPath);

    if (localDefinitionsFile.is_open()) {
        std::string word;
        std::string definition;

        while (!localDefinitionsFile.eof()) {

            std::getline(localDefinitionsFile, word, '\t');
            std::getline(localDefinitionsFile, definition, '\n');

            Word* wordObj = new Word(word);
            auto maybeData = wordSet.find(word);

            if (maybeData == nullptr) {
                wordCollection.push_back(wordObj);
                wordSet.insert(word);
                // TODO: Add definition
            } else {
                // TODO: Add definition to existing word
            }
        }

        localDefinitionsFile.close();
    }

    std::ifstream favoritesFile(favoritesPath);

    if (favoritesFile.is_open()) {
        std::string line;

        while (std::getline(favoritesFile, line, '\n')) {
            auto maybeData = wordSet.find(line);

            if (maybeData == nullptr) {
                std::cout << "[WARN] Favorite word not found in dictionary: " << line;
            }

            // Add favorite.
        }

        favoritesFile.close();
    }

    std::ifstream historyFile(historyPath);

    if (historyFile.is_open()) {
        std::string line;

        while (std::getline(historyFile, line, '\n')) {
            // Do something about it
        }

        historyFile.close();
    }
}
