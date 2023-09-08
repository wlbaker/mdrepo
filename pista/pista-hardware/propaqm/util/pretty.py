
import json


fname = '../../../../doc/trace/propaqm-numerics-data'
with open( fname, 'r') as myfile:
  data = myfile.read()

parsed = json.loads(data)
print( json.dumps(parsed, indent=4, sort_keys=True) )


