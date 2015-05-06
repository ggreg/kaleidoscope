{
  'variables': {
    'gtest_root': '/usr/src/gtest',
    'gtest_source': '<(gtest_root)/src',
    'gtest_local_root': 'third-party/gtest/',
    'gtest_local_source': '<(gtest_local_root)/src',
  },
  'targets': [{
    'target_name': 'googletest',
    'type': 'static_library',
    'sources': [
      '<(gtest_local_source)/gtest-death-test.cc',
      '<(gtest_local_source)/gtest-filepath.cc',
      '<(gtest_local_source)/gtest-port.cc',
      '<(gtest_local_source)/gtest-printers.cc',
      '<(gtest_local_source)/gtest-test-part.cc',
      '<(gtest_local_source)/gtest-typed-test.cc',
      '<(gtest_local_source)/gtest.cc'
    ],
    'copies': [{
      'files': [
        '<(gtest_source)/gtest-death-test.cc',
        '<(gtest_source)/gtest-filepath.cc',
        '<(gtest_source)/gtest-port.cc',
        '<(gtest_source)/gtest-printers.cc',
        '<(gtest_source)/gtest-test-part.cc',
        '<(gtest_source)/gtest-typed-test.cc',
        '<(gtest_source)/gtest.cc',
      ],
      'destination': '<(gtest_local_source)',
    }],
    'include_dirs': [
      '<(gtest_root)',
      '<(gtest_root)/include'
    ],
    'direct_dependent_settings': {
      'include_dirs': [
        '<(gtest_root)',
        '<(gtest_root)/include'
      ]
    },
  },
  {
    'target_name': 'googletest_main',
    'type': 'static_library',
    'sources': ['<(gtest_local_source)/gtest_main.cc'],
    'link_settings': {
      'libraries': [
        '-lpthread',
      ]
    },
    'copies': [{
      'files': [
        '<(gtest_source)/gtest_main.cc'
      ],
      'destination': '<(gtest_local_source)',
    }],
    'dependencies': ['googletest'],
    'export_dependent_settings': ['googletest']
  }]
}
