{
  'variables': {
    'target_arch%': 'x64',
    'vc_runtime%': 'dynamic',
  },
  'target_defaults': {
    'default_configuration': 'Debug',
    'conditions': [
      ['target_arch=="x64"', {
        'msvs_configuration_platform': 'x64',
        'msbuild_settings': {
          'Link': {
            'AdditionalManifestDependencies': [
              'type=\'win32\' name=\'Microsoft.Windows.Common-Controls\' version=\'6.0.0.0\' processorArchitecture=\'amd64\' publicKeyToken=\'6595b64144ccf1df\' language=\'*\'',
            ],
          },
        },
      }],
      ['target_arch=="ia32"', {
        'msbuild_settings': {
          'ClCompile': {
            'CreateHotpatchableImage': 'true',
          },
          'Link': {
            'AdditionalManifestDependencies': [
              'type=\'win32\' name=\'Microsoft.Windows.Common-Controls\' version=\'6.0.0.0\' processorArchitecture=\'x86\' publicKeyToken=\'6595b64144ccf1df\' language=\'*\'',
            ],
          },
        },
      }],
    ],
    'defines': [
      'WIN32_LEAN_AND_MEAN',
      'NOMINMAX',
      '_ATL_CSTRING_EXPLICIT_CONSTRUCTORS',
      '_WTL_NO_CSTRING',
      '_CSTRING_NS_=ATL',
    ],
    'msbuild_configuration_attributes': {
      'CharacterSet': 'Unicode',
    },
    'msbuild_settings': {
      'ClCompile': {
        'WarningLevel': 'Level4',
        'TreatWarningAsError': 'true',
        # 'SDLCheck': 'true',
        'ForcedIncludeFiles': [
          'sdkddkver.h',
        ],
      },
      'Link': {
        'TreatLinkerWarningAsErrors': 'true',
      },
      'Lib': {
        'TreatLibWarningAsErrors': 'true',
      },
      'ResourceCompile': {
        'Culture': '0x0411',
      },
      'Midl': {
        'WarnAsError': 'true',
        'ValidateAllParameters': 'true',
      },
    },
    'configurations': {
      'Debug': {
        'defines': [
          '_DEBUG'
        ],
        'msbuild_configuration_attributes': {
          'LinkIncremental': 'true',
        },
        'msbuild_settings': {
          'ClCompile': {
            'Optimization': 'Disabled',
            'AdditionalOptions': '/sdl /Qspectre',
            'conditions': [
              ['vc_runtime=="dynamic"', {
                'RuntimeLibrary': 'MultiThreadedDebugDLL',
              }],
              ['vc_runtime=="static"', {
                'RuntimeLibrary': 'MultiThreadedDebug',
              }],
            ],
          },
        },
      },
      'Release': {
        'defines': [
          'NDEBUG',
        ],
        'msbuild_configuration_attributes': {
          'LinkIncremental': 'false',
        },
        'msbuild_settings': {
          'ClCompile': {
            'Optimization': 'MaxSpeed',
            'IntrinsicFunctions': 'true',
            # 'ControlFlowGuard': 'Guard',
            'FunctionLevelLinking': 'true',
            'AdditionalOptions': '/sdl /guard:cf /Qspectre',
            'conditions': [
              ['vc_runtime=="dynamic"', {
                'RuntimeLibrary': 'MultiThreadedDLL',
              }],
              ['vc_runtime=="static"', {
                'RuntimeLibrary': 'MultiThreaded',
              }],
            ],
          },
          'Link': {
            'OptimizeReferences': 'true',
            'EnableCOMDATFolding': 'true',
          },
        },
      },
    },
  },
}
