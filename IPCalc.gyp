{
  'target_defaults': {
    'configurations': {
      'Debug': {
      },
      'Release': {
      },
    },
  },
  'targets': [
    {
      'target_name': 'IPCalc',
      'type': 'none',
      'dependencies': [
        'ip_calc/IPCalc.gyp:IPCalc',
      ],
    },
  ],
}
