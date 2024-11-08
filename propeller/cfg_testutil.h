#ifndef PROPELLER_CFG_TESTUTIL_H_
#define PROPELLER_CFG_TESTUTIL_H_

#include <sys/types.h>

#include <cstdint>
#include <memory>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/types/span.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Object/ELFTypes.h"
#include "propeller/cfg.h"
#include "propeller/cfg_edge.h"
#include "propeller/cfg_edge_kind.h"
#include "propeller/cfg_node.h"

namespace propeller {

struct NodeArg {
  uint64_t addr;
  int bb_index;
  uint64_t size;
  llvm::object::BBAddrMap::BBEntry::Metadata metadata;
};

struct IntraEdgeArg {
  int from_bb_index;
  int to_bb_index;
  int weight;
  propeller::CFGEdgeKind kind;
};

struct InterEdgeArg {
  int from_function_index;
  int from_bb_index;
  int to_function_index;
  int to_bb_index;
  int weight;
  propeller::CFGEdgeKind kind;
};

struct CfgArg {
  llvm::StringRef section_name;
  int function_index;
  llvm::StringRef function_name;
  const std::vector<NodeArg> node_args;
  const std::vector<IntraEdgeArg> edge_args;
};

struct MultiCfgArg {
  const std::vector<CfgArg> cfg_args;
  const std::vector<InterEdgeArg> inter_edge_args;
};

// Utility class for building a CFG for tests.
class TestCfgBuilder {
 public:
  TestCfgBuilder(const TestCfgBuilder &) = delete;
  TestCfgBuilder &operator=(const TestCfgBuilder &) = delete;
  TestCfgBuilder(TestCfgBuilder &&) = delete;
  TestCfgBuilder &operator=(TestCfgBuilder &&) = delete;

  explicit TestCfgBuilder(MultiCfgArg multi_cfg_arg)
      : multi_cfg_arg_(multi_cfg_arg) {}

  // Builds and returns the CFG.
  absl::flat_hash_map<int, std::unique_ptr<propeller::ControlFlowGraph>> Build()
      &&;

 private:
  // Creates and returns a vector of nodes corresponding to one CFG with
  // `function_index` for every `NodeArg` specified in `args`, in the same
  // order.
  std::vector<std::unique_ptr<propeller::CFGNode>> CreateNodesForCfg(
      int function_index, absl::Span<const NodeArg> args);

  // Creates intra-function edges for `cfg` for every `IntraEdgeArg` specified
  // in `args`.
  void CreateIntraEdgesForCfg(propeller::ControlFlowGraph &cfg,
                              absl::Span<const IntraEdgeArg> args);

  // Creates inter-function edges for every `InterEdgeArg` specified in `args`.
  void CreateInterEdges(absl::Span<const InterEdgeArg> args);

  MultiCfgArg multi_cfg_arg_;
  // Created CFGs mapped by their function_index.
  absl::flat_hash_map<int, std::unique_ptr<propeller::ControlFlowGraph>>
      cfgs_by_function_index_;
  // Created nodes mapped first by their function_index and then by their
  // bb_index.
  absl::flat_hash_map<int, absl::flat_hash_map<int, propeller::CFGNode *>>
      nodes_by_function_and_bb_index_;
};
}  // namespace propeller

#endif  // PROPELLER_CFG_TESTUTIL_H_
