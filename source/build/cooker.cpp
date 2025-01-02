/*
Content cooker. When this program is run, it is iterating over all subdirectories of assets/, with the exception of the
test/ subdirectory. How it works is described in the code.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#include <lz4.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
/* ------------------------------------------------------------------------------------------------------------------ */
namespace fs = std::filesystem;
/* ------------------------------------------------------------------------------------------------------------------ */
std::vector<fs::path> gatherFilePaths() {
  std::vector<fs::path> files;

  try {
    for (auto it = fs::recursive_directory_iterator("assets"); it != fs::recursive_directory_iterator(); ++it) {
      if (it->is_directory() && it->path().filename() == "test") {
        // Skip the excluded directory and its contents
        it.disable_recursion_pending();
        continue;
      }

      if (it->is_regular_file()) {
        files.push_back(it->path());
      }
    }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
  }

  return files;
}
/* ------------------------------------------------------------------------------------------------------------------ */
int main() {
  std::vector<fs::path> filePaths = gatherFilePaths();

  for (const auto& filePath : filePaths) {
    std::ifstream fileHandle(filePath.string(), std::ios::binary | std::ios::ate);
    if (!fileHandle.is_open()) {
      std::cerr << "Failed to open file " << filePath.string() << "\n";
      return 1;
    }

    int fileSize = fileHandle.tellg();
    fileHandle.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    fileHandle.read(buffer.data(), fileSize);
    fileHandle.close();

    // Dynamically allocate buffers to handle large data
    char* compressed = new char[LZ4_compressBound(fileSize)];
    memset(compressed, 0, LZ4_compressBound(fileSize));

    char* decompressed = new char[fileSize + 1];  // +1 for null terminator
    memset(decompressed, 0, fileSize + 1);

    // Compress
    int compressedSize = LZ4_compress_fast(buffer.data(), compressed, fileSize, LZ4_compressBound(fileSize), 1);
    if (compressedSize <= 0) {
      std::cerr << "Compression failed!\n";
      delete[] compressed;
      delete[] decompressed;
      return 1;
    }
    std::printf("Compression successful, before/after: %d/%d\n", fileSize, compressedSize);

    // Decompress
    int decompressedSize = LZ4_decompress_safe(compressed, decompressed, compressedSize, fileSize);
    if (decompressedSize < 0) {
      std::cerr << "Decompression failed!\n";
      delete[] compressed;
      delete[] decompressed;
      return 1;
    }
    std::cout << "Decompression successful: " << decompressed << "\n";

    delete[] compressed;
    delete[] decompressed;
  }

  return 0;
}
/* ------------------------------------------------------------------------------------------------------------------ */