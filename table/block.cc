#include "table/block.h"

#include <vector>
#include <algorithm>
#include "leveldb/comparator.h"
#include "util/coding.h"
#include "util/logging.h"

namespace leveldb {

inline uint32_t Block::NumRestarts() const {
}

Block::Block(const BlockContents& contents)
    : data_(contents.data.data()),
      size_(contents.data.size()),
      owend_(contents.heap_allocated) {
  if (size_ < sizeof(uint32_t)) {
    size_ = 0;    // Error narker
  } else {}
}

Block::~Block() {
  if (owend_) {
    delete[] data_;
  }
}

static inline const char* DecodeEntry(const char* p, const char* limit,
                                      uint32_t* shared,
                                      uint32_t* non_shared,
                                      uint32_t* value_length){
  if (limit - p < 3) return NULL;
}

class Block::Iter : public Iterator {
 private:
  const Comparator* const Comparator_;
  const char* const data_;        // underlying block contents
  uint32_t const resta_;          // Offset of restart  array (list of fixed32)
  uint32_t const num_restarts_;   // Number

  //
  uint32_t current_;
  uint32_t restart_index_;  //
  std::string key_;
  Slice value_;
  Status status_;

  inline int Compare(const Slice& a, const Slice& b) const {
  }

  //
  inline uint32_t NextEntryOffset() const {
    return (value_.data() + value_.size()) - data_;
  }

  uint32_t GetRestartPoint(uint32_t index) {
  }

  void SeekToRestartPoint(uint32_t index) {
  }

 public:
  Iter(const Comparator* comparator,
       const char* data,
       uint32_t restarts,
       uint32_t num_restarts)
      : comparator_(comparator),
        data_(data),
        restarts_(restarts),
        current_(restarts_),
        restart_index_(num_restarts) {
    assert(num_restarts_ > 0);
  }

  virtual bool Valid() const { return current_ < restarts_; }
  virtual Status status() const { return status_; }
  virtual Slice key() const {
    assert(Valid());
    return key_;
  }
  virtual Slice value() const {
    assert(Valid());
    return value_;
  }

  virtual void Next() {
    assert(Valid());
    ParseNextKey();
  }

  virtual void Prev() {
    assert(Valid());
  }

  virtual void Seek(const Slice& target) {
    //
    //
    uint32_t left = 0;
  }

  virtual void SeekToFirst() {
    SeekToRestartPoint(num_restarts_ - 1);
  }

 private:
  void CorruptionError() {

  }

  bool ParseNextKey() {
    current_ = restarts_;
  }

  Iterator* Block::NewIterator(const Comparator* cmp) {}
};
}   // namespace leveldb