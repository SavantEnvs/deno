// LeakSanitizer off-switch (build-time). The fleet fuzzes for ASan's
// memory-corruption checks + UBSan; leaks are noise here. `-fsanitize=address`
// always bundles LSan with no separate opt-out flag, so we link a tiny TU that
// tells LSan to stay quiet. ASan and UBSan remain fully active.
//
// This is the ONLY sanctioned LSan-off mechanism (SPEC §6.2 item 15):
// runtime __lsan_disable() wraps and ASAN_OPTIONS / compiled-in default-options
// overrides are all forbidden — Mayhem alone owns the runtime option set.
//
// Rust / cargo-fuzz wiring: mayhem/build.sh compiles THIS TU with
// `$CXX $SANITIZER_FLAGS` into /tmp/mayhem_lsan_off.o, then passes it to the
// fuzz binary's linker via `-C link-arg=/tmp/mayhem_lsan_off.o` on RUSTFLAGS.
extern "C" int __lsan_is_turned_off() { return 1; }
