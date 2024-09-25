# ---------------------------------------------------------------------------
# cengine
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Library
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/mmapvector/local.cmake")

# Tools

include("${CMAKE_CURRENT_LIST_DIR}/datasets/stats/string-stats/local.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/datasets/stats/double-stats/local.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/datasets/stats/integer-stats/local.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/conversion/local.cmake")

# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_clang_tidy_target(lint_tools "${TOOLS_SRC}")
list(APPEND lint_targets lint_tools)
