/*
Content cooker. When this program is run, it is iterating over all subdirectories of assets/, with the exception of the
test/ subdirectory. How it works is described in the code.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#include <lz4.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
/* ------------------------------------------------------------------------------------------------------------------ */
namespace fs = std::filesystem;
/* ------------------------------------------------------------------------------------------------------------------ */
struct Archive {
  char header[32];
  std::vector<std::string> paths;
  std::vector<uint64_t> positions;
  std::vector<uint64_t> compressedSizes;
  std::vector<uint64_t> decompressedSizes;
  std::vector<char*> compressedDatas;
};
/* ------------------------------------------------------------------------------------------------------------------ */
std::vector<fs::path> gather_asset_paths() {
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
    std::fprintf(stderr, "Filesystem error: %s\n", e.what());
  }

  return files;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void dump_to_disk(Archive* archive) {
  std::ofstream fileHandle("assets.data", std::ios::out | std::ios::binary);
  if (!fileHandle.is_open()) {
    std::fprintf(stderr, "Could not open assets.dat for archive dump.");
    std::exit(1);
  }

  fileHandle << archive->header << "\n";
  for (int i = 0; i < archive->paths.size(); ++i) {
    fileHandle << archive->paths[i] << " " << archive->positions[i] << " " << archive->compressedSizes[i] << " "
               << archive->decompressedSizes[i] << "\n";
  }
  for (const auto& compressedData : archive->compressedDatas) {
    fileHandle << compressedData;
    delete[] compressedData;
  }

  fileHandle.close();
  std::printf("Asset archive created.\n");
}
/* ------------------------------------------------------------------------------------------------------------------ */
Archive create_archive(const std::vector<fs::path>& assetPaths) {
  Archive archive;
  strcpy(archive.header, "LMent data");
  archive.paths.reserve(assetPaths.size());
  archive.positions.reserve(assetPaths.size());
  archive.compressedSizes.reserve(assetPaths.size());
  archive.decompressedSizes.reserve(assetPaths.size());
  archive.compressedDatas.reserve(assetPaths.size());

  uint64_t archivedDataPosition{0};

  for (const auto& assetPath : assetPaths) {
    std::ifstream assetHandle(assetPath.string(), std::ios::binary | std::ios::ate);
    if (!assetHandle.is_open()) {
      std::fprintf(stderr, "Failed to open file: %s\n", assetPath.string().c_str());
      std::exit(1);
    }

    const int fileSize = assetHandle.tellg();
    assetHandle.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    assetHandle.read(buffer.data(), fileSize);
    assetHandle.close();

    // Potentially very large files, so dynamic allocation is required.
    char* compressed = new char[LZ4_compressBound(fileSize)];
    memset(compressed, 0, LZ4_compressBound(fileSize));

    // Compress
    const int compressedSize = LZ4_compress_fast(buffer.data(), compressed, fileSize, LZ4_compressBound(fileSize), 1);
    if (compressedSize <= 0) {
      std::fprintf(stderr, "Compression of file \"%s\" failed.\n", assetPath.string().c_str());
      delete[] compressed;
      std::exit(1);
    }
    std::printf("Compression of file \"%s\" successful, before/after: %d/%d\n", assetPath.string().c_str(), fileSize,
                compressedSize);

    archive.paths.emplace_back(assetPath.string());
    archive.positions.emplace_back(archivedDataPosition);
    archive.compressedSizes.emplace_back(compressedSize);
    archive.decompressedSizes.emplace_back(fileSize);
    archive.compressedDatas.emplace_back(compressed);

    archivedDataPosition += compressedSize;
  }

  return archive;
}
/* ------------------------------------------------------------------------------------------------------------------ */
int main() {
  std::vector<fs::path> filePaths = gather_asset_paths();
  Archive archive = create_archive(filePaths);
  dump_to_disk(&archive);

  return 0;
}
/* ------------------------------------------------------------------------------------------------------------------ */