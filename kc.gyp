{
    'targets': [{
        'target_name': 'kc',
        'type': 'executable',
        'sources': [
            'src/main.cc',
        ],
        'cflags': [
            '-std=c++11',
            '-Werror',
        ],
    }, {
        'target_name': 'tests/test',
        'type': 'executable',
        'dependencies': [
            'test.gyp:googletest_main',
        ],
        'sources': [
            'tests/test_main.cc',
        ]
    }]
}
