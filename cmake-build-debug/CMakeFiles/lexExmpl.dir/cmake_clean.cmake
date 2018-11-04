file(REMOVE_RECURSE
  "generated"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/lexExmpl.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
