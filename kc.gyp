{
    'targets': [{
        'target_name': 'kaleidoscope++',
        'type': 'static_library',
        'include_dirs': [
            'src',
        ],
        'sources': [
            'src/lexer.cpp',
        ],
        'cflags': [
            '-std=c++11',
            '-Werror',
        ],
        'link_settings': {
            'libraries': [
                '-lstdc++',
            ]
        },
    },{
        'target_name': 'kc',
        'type': 'executable',
        'sources': [
            'src/main.cc',
        ],
        'cflags': [
            '-std=c++11',
            '-Werror',
        ],
        'dependencies': [
            'test.gyp:googletest_main',
            'kaleidoscope++',
        ],
        'link_settings': {
            'libraries': [
                '-lstdc++',
            ]
        },
    }, {
        'target_name': 'tests/test',
        'type': 'executable',
        'cflags': [
            '-std=c++11',
            '-Werror',
        ],
        'link_settings': {
            'libraries': [
                '-lstdc++',
            ]
        },
        'dependencies': [
            'test.gyp:googletest_main',
            'kaleidoscope++',
        ],
        'include_dirs': [
            'src',
        ],
        'sources': [
            'tests/test_main.cc',
            'tests/test_lexer.cpp',
        ]
    }]
}
