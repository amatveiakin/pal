[cc_test(
    name = f[:-4],
    srcs = [f],
    deps = [
        "//:pal",
        "@googletest//:gtest_main",
    ],
) for f in glob(["*.cpp"])]
