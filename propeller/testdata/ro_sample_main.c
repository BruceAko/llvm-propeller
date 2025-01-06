// Copyright 2024 The Propeller Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// To build ro_sample.out:
// clang -fuse-ld=lld -Wl,-build-id ro_sample_main.c libro_sample.so
// -Wl,-build-id -Wl,-rpath,. -o ro_sample.out

int foo();

int main() { return foo(); }
