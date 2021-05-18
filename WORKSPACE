load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_cc",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/262ebec3c2296296526740db4aefce68c80de7fa.zip"],
    sha256 = "9a446e9dd9c1bb180c86977a8dc1e9e659550ae732ae58bd2e8fd51e15b2c91d",
    strip_prefix = "rules_cc-262ebec3c2296296526740db4aefce68c80de7fa",
)

http_archive(
    name = "absl",
    urls = ["https://github.com/abseil/abseil-cpp/archive/aad2c8a3966424bbaa2f26027d104d17f9c1c1ae.zip"],
    strip_prefix = "abseil-cpp-aad2c8a3966424bbaa2f26027d104d17f9c1c1ae",
    sha256 = "63d606fc19c56aa7b20c7c398781a40ae1f8321fab43be230b1eb46dbbee77f7",
)

http_archive(
    name = "googletest",
    urls = ["https://github.com/google/googletest/archive/703bd9caab50b139428cea1aaff9974ebee5742e.zip"],
    strip_prefix = "googletest-703bd9caab50b139428cea1aaff9974ebee5742e",
    sha256 = "2db427be8b258ad401177c411c2a7c2f6bc78548a04f1a23576cc62616d9cd38",
    build_file = "gmock.BUILD",
)
