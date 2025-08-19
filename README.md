# NFSC-ChallengeSeriesRaceIconFix
此 ASI 插件用于修复 Need for Speed Carbon 自定挑战赛图标显示问题<br>

游戏将挑战赛按索引分组，每组有3个挑战赛，同一个事件组中的所有挑战赛应用相同的图标<br>
这意味着您在改变其中一场挑战赛图标时，同一行中所有的图标都将会同时更变<br>
这可能会在未来修复或解决<br>

您需要根据自身需求自行编辑代码并编译它<br>

在代码开始的常量定义中，您可以找到对于挑战赛图标以及挑战赛本身的哈希值定义<br>

例如：<br>
const unsigned int CUSTOM_CHALLENGE_HASH_1 = 0x00000000;<br>
const 无符号 int CUSTOM_CHALLENGE_HASH_2 = 0x00000000;<br>
常量无符号 int CUSTOM_CHALLENGE_HASH_3 = 0x00000000;<br>

以及：<br>
const unsigned int CHALLENGERACE_ICON_HASH_1 = 0x00000000;<br>
const unsigned int CHALLENGERACE_ICON_HASH_2 = 0x00000000;<br>
const 无符号 int CHALLENGERACE_ICON_HASH_3 = 0x00000000;<br>

对于图标哈希值，您可以在 Binary 中查看图标的哈希值，其中 BinKey 即为它们的哈希值<br>
对于挑战赛哈希值，您可以通过我的 https://github.com/LEE-YAMADARYO/NFSC-GetChallengeSeriesRaceHash 解决方案获取<br>

在 char __stdcall DetourGetChallengeEventIcon 函数中，您则可以直接定义您所添加的挑战赛调用的图标<br>

待办/计划：<br>
更精确的修改单个挑战赛图标而不会将整行的图标全部更变<br>
