#-------------------------------------------------------------------------------------------
# Copyright (c) 2024, SkillerRaptor
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

include(FetchContent)

#-------------------------------------------------------------------------------------------
# argparse
#-------------------------------------------------------------------------------------------
FetchContent_Declare(
        Catch2
        SYSTEM
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG fa43b77429ba76c462b1898d6cd2f2d7a9416b14)

set(CATCH_INSTALL_DOCS OFF CACHE INTERNAL "")
set(CATCH_INSTALL_EXTRAS OFF CACHE INTERNAL "")
set(CATCH_DEVELOPMENT_BUILD OFF CACHE INTERNAL "")
set(CATCH_ENABLE_REPRODUCIBLE_BUILD ON CACHE INTERNAL "")

FetchContent_MakeAvailable(Catch2)

set_target_properties(
        Catch2
        PROPERTIES
        FOLDER "third_party")
set_target_properties(
        Catch2WithMain
        PROPERTIES
        FOLDER "third_party")