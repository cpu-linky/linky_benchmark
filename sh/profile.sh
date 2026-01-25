#!/usr/bin/env bash
# Author : Pallandos
# -------------------------------------------------------
# profile.sh
# This file does this
#
# TODO : usage
#
# -------------------------------------------------------

set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"

######################################
# ====== Constants and variables =====
######################################

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# ---- Helpers ----
error_exit() { # print an error message and exit
    echo -e "${RED}ERROR: $1${NC}" >&2
    exit 1
}

print_info() { # print an info message
    echo -e "${CYAN}INFO: $1${NC}"
}

print_warning() { # print a warning message
    echo -e "${YELLOW}WARNING: $1${NC}" >&2
}

print_success() { # print a success message
    echo -e "${GREEN}SUCCESS: $1${NC}"
}

######################################
# ============ Functions =============
######################################

check_requirements() {
    errors=0
    if ! command -v turbostat >/dev/null 2>&1; then 
        print_warning "turbostat is not installed and required"
        errors=$((errors + 1))
    fi

    if [ $errors -gt 0 ]; then
        error_exit "$errors requirements are missing. Please install them and try again."
    fi
}

run_with_stats() {
    turbostat --interval 1 --quiet \
    ../out/bin/cstate_monitor
}


######################################
# =========== Main Logic =============
######################################

main() {
    check_requirements
    
    run_with_stats
}

main "$@"