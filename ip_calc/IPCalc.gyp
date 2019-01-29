{
  'includes': [
    '../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'IPCalc',
      'product_name': 'IPCalc',
      'type': 'executable',
      'include_dirs': [
        '.',
        '../third_party/wtl/Include',
      ],
      'defines': [
        '_WINDOWS',
      ],
      'msbuild_settings': {
        'Link': {
          'SubSystem': 'Windows',
        },
        'Manifest': {
          'EnableDPIAwareness': 'true',
        },
      },
      'sources': [
        'app/application.cc',
        'app/application.h',
        'res/resource.h',
        'res/resource.rc',
        'ui/main_dialog.cc',
        'ui/main_dialog.h',
      ],
    },
  ],
}
