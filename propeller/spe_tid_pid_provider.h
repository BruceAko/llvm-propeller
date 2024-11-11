#ifndef PROPELLER_SPE_TID_PID_PROVIDER_H_
#define PROPELLER_SPE_TID_PID_PROVIDER_H_

#include <sys/types.h>

#include <cstdint>

#include "absl/container/btree_map.h"
#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "propeller/spe_pid_provider.h"
#include "src/quipper/arm_spe_decoder.h"
#include "src/quipper/perf_data.pb.h"
#include "google/protobuf/repeated_ptr_field.h"

namespace propeller {

// An SPE PID provider which reads the TID from the context field. It requires
// that the perf.data the instruction record comes from file was collected with
// a kernel built with CONFIG_PID_IN_CONTEXTIDR=y.
class SpeTidPidProvider : public SpePidProvider {
 public:
  // Constructs a provider based on the TIDs and PIDs in `events`.
  explicit SpeTidPidProvider(
      const google::protobuf::RepeatedPtrField<quipper::PerfDataProto_PerfEvent>& events);

  // SpeTidPidProvider is copyable and movable.
  SpeTidPidProvider(const SpeTidPidProvider&) = default;
  SpeTidPidProvider(SpeTidPidProvider&&) = default;
  SpeTidPidProvider& operator=(const SpeTidPidProvider&) = default;
  SpeTidPidProvider& operator=(SpeTidPidProvider&&) = default;

  absl::StatusOr<int> GetPid(
      const quipper::ArmSpeDecoder::Record& record) const override;

 private:
  // Converts an SPE timestamp (which uses TSC time) to a perf timestamp (which
  // uses perf time).
  uint64_t SpeTimestampToPerfTimestamp(uint64_t cycles) const;

  // TID -> (timestamp -> pid)
  absl::flat_hash_map<int, absl::btree_map<uint64_t, pid_t>> tids_to_pids_;
  quipper::PerfDataProto::TimeConvEvent time_conv_event_;
};
}  // namespace propeller

#endif  // PROPELLER_SPE_TID_PID_PROVIDER_H_
