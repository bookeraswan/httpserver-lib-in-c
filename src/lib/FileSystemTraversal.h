#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

namespace FileSystemTraversal{
    void traverseFileSystemTreeUnder(std::string path, std::vector<std::string>* fileList){
        for (const auto & entry : std::filesystem::directory_iterator(path)){
            if(entry.is_directory()){
                traverseFileSystemTreeUnder(entry.path(), fileList);
            }
            else{
                fileList->push_back(entry.path());
            }
        }
    }

    std::vector<std::string> filesUnderDirectory(std::string path){
        std::vector<std::string> list;
        traverseFileSystemTreeUnder(path, &list);
        return list;
    }
};