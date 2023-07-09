
|num|data|ret|jxx|F|D|E|M|W|
|-|-|-|-|-|-|-|-|-|
|1|0|0|0|X|X|X|X|X|
|2|0|0|1|X|bubble|bubble|X|X|
|3|0|1|0|stall|bubble|X|X|X|
|4|1|0|0|stall|stall|bubble|X|X|
|5|0|1|1|X|bubble|bubble|X|X|
|6|1|0|1|X|bubble|bubble|X|X|
|7|1|1|0|stall|stall|bubble|X|X|
|8|1|1|1|X|bubble|bubble|X|X|


F:

- stall: (data || ret) && !jxx
- bubble: 0

D:

- stall: data && !jxx
- bubble: jxx || (!data && ret)

E:

- stall: 0
- bubble: jxx || data

M:

keep same

W:

keep same