#include "extractor.h"

namespace bib_ocr {

Extractor::Extractor(const std::string& filename) : filename_(filename) {
  image_ = cv::imread(filename);
  // TODO(kareth) read image_handler header file
  ImageHandler::set_filename(filename);
}

Extractor::~Extractor() {
}

int Extractor::Extract() {
  BlockSeparator separator(&image_);
  if (separator.Separate() == -1)
    return -1;

  ExtractNumbers(separator.GetBlocks());
  return 0;
}

void Extractor::ExtractNumbers(const std::vector<cv::Mat>& blocks) {
  for (auto block : blocks) {
    NumberReader reader(&block);
    if (reader.Read() == 0)
      AddResult(reader.GetNumber());
  }
}

void Extractor::AddResult(const Result& result) {
  numbers_.push_back(result);
  return;
}

}  // namespace bib_ocr