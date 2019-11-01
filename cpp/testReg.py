import re

data = "----\n\nhello\nworld\n----\nhello\n----"
# res = re.search("\-{4}\n([^-]\n*)*\-{4}", data+data)
res = re.findall("\-*[^-]*\-{3}", data)
print(res)