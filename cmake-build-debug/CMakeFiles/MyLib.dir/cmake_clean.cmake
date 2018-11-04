file(REMOVE_RECURSE
  "/src/rcdgen/scanner.cpp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/MyLib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
