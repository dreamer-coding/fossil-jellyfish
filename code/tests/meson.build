if get_option('with_test').enabled()
    run_command(['python3', 'tools' / 'generate-runner.py'], check: true)

    test_c   = ['unit_runner.c']
    test_cases = [
        'jellyfish'
    ]

    foreach cases : test_cases
        test_c += ['cases' / 'test_' + cases + '.c']
        test_c += ['cases' / 'test_' + cases + '.cpp']
    endforeach

    pizza_c = executable('testbed-c', test_c, include_directories: dir,
        dependencies: [subproject('fossil-test').get_variable('fossil_test_dep'), fossil_fish_dep])

    test('fossil testing C', pizza_c)
endif
