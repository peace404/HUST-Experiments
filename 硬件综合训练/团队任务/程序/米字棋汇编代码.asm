.text

draw_board:
    # Prologue: 保存 ra
    addi a5, zero, 3     ## 横竖各画2条线
    addi a6, zero, 116   ## 线从3到124号的像素
    addi a4, zero, 0
    addi s6, zero, -43

    ## 绘制2条横线
Hengxian:
    addi s6, s6, 53
    addi s10, zero, 10    # 使用 s10 替代 sp
Heng_Dian:
    addi s10, s10, 1        # 原先错误地修改 sp，现在使用 s10
    addi s5, zero, 2
    ecall                ## 画像素点
    bne  s10, a6, Heng_Dian
    addi a4, a4, 1
    bne  a4, a5, Hengxian

    ## 绘制2条竖线
    addi a4, zero, 0
    addi s10, zero, -43    # 使用 s10 替代 sp
Shuxian:
    addi s10, s10, 53        # 原先错误地修改 sp，现在使用 s10
    addi s6, zero, 10
Shu_Dian:
    addi s6, s6, 1
    addi s5, zero, 2
    ecall                ## 画像素点
    bne  s6, a6, Shu_Dian
    addi a4, a4, 1
    bne  a4, a5, Shuxian

    ## 绘制右斜线
    addi s6, zero, 10
    addi s10, zero, 10     # 使用 s10 替代 sp
    addi a5, zero, 117
YouXieXian:
    addi s5, zero, 2
    ecall
    addi s10, s10, 1        # 原先错误地修改 sp，现在使用 s10
    addi s6, s6, 1
    bne  s6, a5, YouXieXian

    ## 绘制左斜线
    addi s6, zero, 116
    addi s10, zero, 10     # 使用 s10 替代 sp
    addi a5, zero, 117
ZuoXieXian:
    addi s5, zero, 2
    ecall
    addi s10, s10, 1        # 原先错误地修改 sp，现在使用 s10
    addi s6, s6, -1
    bne  s10, a5, ZuoXieXian

main:
##$13（a7）寄存器用于记录当前棋盘状态 0000 0000 0000 00xx xxxx xxxx xxxx xxxx
# 构造 0x2a015
addi a7, zero, 0
addi s5, zero, 3
ecall

addi a7, zero, 0x2a         # a7 = 0x520
slli a7, a7, 12              # a7 = 0x520000
addi a7, a7, 0x15           # a7 = 0x520025

##$11（a1）寄存器用于存放下棋的用户，0表示蓝色（01）在下棋，1表示红色（10）在下棋
addi a1,zero,0
##$18（s2）用于表示是第几次按钮，如果是0表示第一次，1表示第二次
addi s2,zero,0
##$19（s3）按下的按钮是什么 1111 1111 1111 11/11 1111 1111 1111 1100表示按下了第一位
addi a2,zero,0

addi s5, zero, 1
ecall


JZQ_Loop:
addi a4,zero,1
j JZQ_Loop


## 按钮1中断处理
Interupt1:
    addi t0,zero, 0      ## 按钮1掩码
    jal Handle_Button

## 按钮2中断处理
Interupt2:
    addi t0,zero, 1      ## 按钮2掩码
    jal Handle_Button

## 按钮3中断处理
Interupt3:
    addi t0,zero, 2      ## 按钮3掩码
    jal Handle_Button

## 按钮4中断处理
Interupt4:
    addi t0,zero, 3      ## 按钮4掩码
    jal Handle_Button

## 按钮5中断处理
Interupt5:
    addi t0,zero, 4      ## 按钮5掩码
    jal Handle_Button

## 按钮6中断处理
Interupt6:
    addi t0,zero, 5      ## 按钮6掩码
    jal Handle_Button

## 按钮7中断处理
Interupt7:
    addi t0,zero, 6      ## 按钮7掩码
    jal Handle_Button

## 按钮8中断处理
Interupt8:
    addi t0,zero, 7      ## 按钮8掩码
    jal Handle_Button

## 按钮9中断处理
Interupt9:
    addi t0,zero, 8      ## 按钮9掩码
    jal Handle_Button

Interupt10:
    j main

##t0储存按下按钮的掩码


Handle_Button:
    ## 判断是第一次还是第二次按下
    addi t1, zero, 1          ## t1用来暂存比较的数
    beq s2, t1, second_press  ## 如果是第二次按下，跳转到第二次按下逻辑

    ## 第一次按钮按下逻辑
    slli t4, t0, 1
    srl  t5, a7, t4         # 将目标棋子的两位移到最低位
    andi t2, t5, 3          # 提取最低两位 (屏蔽其余位)

    bne a1, zero, red_turn    ## 如果是红色玩家
    ## 蓝色玩家逻辑
    addi t3, zero, 1          ## 蓝色棋子状态 (01)
    bne t2, t3, end_handle    ## 如果按钮位置不是蓝色棋子，结束处理
    
    ##如果按钮是蓝色棋子,更新状态为第二次按钮（但不修改 a7 寄存器）
    addi s2, zero ,1           ## 按键次数+1，t0存的是第一次按下的键，a7棋局状态没有变过
    or s3, zero, t0           ## 保存第一次按下的掩码（只用于临时判断，不更新棋盘状态）
    uret

red_turn:
    addi t3, zero, 2          ## 红色棋子状态 (10)
    bne t2, t3, end_handle    ## 如果按钮位置不是红色棋子，结束处理

    ## 更新状态为第二次按钮（但不修改 a7 寄存器）
    addi s2, zero, 1          ## 设置为第二次按钮状态
    or s3, zero, t0           ## 保存第一次按下的掩码（只用于临时判断，不更新棋盘状态）
    j end_handle



## 第二次按钮按下逻辑
second_press:
        slli t4, t0, 1
        srl  t5, a7, t4         # 将目标棋子的两位移到最低位
        andi t2, t5, 3          # 提取最低两位 (屏蔽其余位)

    beq t2, zero, valid_move  ## 如果目标位置为空，允许移动

    ## 目标位置不为空，非法移动，恢复到第一次按下前的状态
    addi s2, zero, 0          ## 重置状态按钮为第一次按下
    j end_handle


valid_move:
    ## 检查第二次按下的按钮（t0）
    addi t1, zero, 0          ## 按钮1的掩码
    beq t0, t1, Check_Button1  ## 如果 t0 是按钮1，跳转到按钮1的合法性检查

    addi t1, zero, 1          ## 按钮2的掩码
    beq t0, t1, Check_Button2  ## 如果 t0 是按钮2，跳转到按钮2的合法性检查

    addi t1, zero, 2          ## 按钮3的掩码
    beq t0, t1, Check_Button3  ## 如果 t0 是按钮3，跳转到按钮3的合法性检查

    addi t1, zero, 3          ## 按钮4的掩码
    beq t0, t1, Check_Button4  ## 如果 t0 是按钮4，跳转到按钮4的合法性检查

    addi t1, zero, 4          ## 按钮5的掩码
    beq t0, t1, Check_Button5  ## 如果 t0 是按钮5，跳转到按钮5的合法性检查

    addi t1, zero, 5          ## 按钮6的掩码
    beq t0, t1, Check_Button6  ## 如果 t0 是按钮6，跳转到按钮6的合法性检查

    addi t1, zero, 6          ## 按钮7的掩码
    beq t0, t1, Check_Button7  ## 如果 t0 是按钮7，跳转到按钮7的合法性检查

    addi t1, zero, 7          ## 按钮8的掩码
    beq t0, t1, Check_Button8  ## 如果 t0 是按钮8，跳转到按钮8的合法性检查

    addi t1, zero, 8          ## 按钮9的掩码
    beq t0, t1, Check_Button9  ## 如果 t0 是按钮9，跳转到按钮9的合法性检查

    ## 如果 t0 不匹配任何按钮掩码，非法
    addi s2, zero, 0           ## 重置状态为第一次按下
    j end_handle

## 按钮1合法性检查
Check_Button1:
    addi t1, zero, 1          ## 按钮2的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 3          ## 按钮4的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move             ## 否则非法

## 按钮2合法性检查
Check_Button2:
    addi t1, zero, 0          ## 按钮1的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 2          ## 按钮3的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move             ## 否则非法

## 按钮3合法性检查
Check_Button3:
    addi t1, zero, 1          ## 按钮2的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 5          ## 按钮6的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move            ## 否则非法

## 按钮4合法性检查
Check_Button4:
    addi t1, zero, 0          ## 按钮1的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 6          ## 按钮7的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move            ## 否则非法

## 按钮5合法性检查
Check_Button5:
    j Check_Valid              ## 按钮5没有限制，直接跳转到合法逻辑

## 按钮6合法性检查
Check_Button6:
    addi t1, zero, 2          ## 按钮3的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 8          ## 按钮9的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move             ## 否则非法

## 按钮7合法性检查
Check_Button7:
    addi t1, zero, 3          ## 按钮4的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 7          ## 按钮8的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move             ## 否则非法

## 按钮8合法性检查
Check_Button8:
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 6          ## 按钮7的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 8          ## 按钮9的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move             ## 否则非法

## 按钮9合法性检查
Check_Button9:
    addi t1, zero, 4          ## 按钮5的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 5          ## 按钮6的掩码
    beq s3, t1, Check_Valid
    addi t1, zero, 7          ## 按钮8的掩码
    beq s3, t1, Check_Valid
    j Invalid_Move             ## 否则非法

## 处理非法移动
Invalid_Move:
    addi s2, zero, 0           ## 重置状态为第一次按下
    j end_handle               ## 跳转到结束逻

Check_Valid:
    ## 执行棋子移动逻辑

    addi t4, zero, 3
    slli t5, s3, 1
    sll  t5, t4, t5         # 将目标棋子的两位移到最低位
    xori t5, t5, -1
    and a7, a7, t5             ## 清除原棋子位置

    ## 检查当前玩家并设置目标位置
    beq a1, zero, Set_Blue     ## 如果是蓝色玩家，跳转到 Set_Blue
    ##红色玩家

    slli t4, t0, 1
    addi t3, zero, 0x2
    sll t4, t3, t4
    or a7, a7, t4                ## 将目标位置写入棋盘状态寄存器
    j Finish_Move              ## 跳转到完成移动逻辑

Set_Blue:
    slli t4, t0, 1
    addi t3, zero, 0x1
    sll t4, t3, t4
    or a7, a7, t4              ## 将目标位置写入棋盘状态寄存器
    j Finish_Move              ## 跳转到完成移动逻辑



## 完成移动
Finish_Move:
    ## 切换玩家
    addi s5, zero, 1
    ecall
    addi s2, zero, 0           ## 重置状态为第一次按下
    ## 检查胜负条件
    jal Process_Last_Button    ## 调用通用胜负判断函数
    j end_handle

end_handle:
    j end_interrupt




Process_Last_Button:
    ## 参数：棋盘状态在 a7，当前玩家在 a1

    bne a1, zero, red_turn_check ## 如果是红色玩家，跳转到红色胜负判断

    ## 蓝色玩家胜负判断
        # 胜利条件1: 0x15000
        addi t0, zero, 0x15
        slli t0, t0, 12           # t0 = 0x15000
        and t2, a7, t0
        beq t2, t0, Win

        # 胜利条件2: 0x540
        addi t0, zero, 0x54
        slli t0, t0, 4            # t0 = 0x540
        and t2, a7, t0
        beq t2, t0, Win

        # 胜利条件3: 0x4104
        addi t0, zero, 0x41
        slli t0, t0, 8            # t0 = 0x4100
        addi t0, t0, 0x4          # t0 = 0x4104
        and t2, a7, t0
        beq t2, t0, Win

        # 胜利条件4: 0x1041
        addi t0, zero, 0x10
        slli t0, t0, 8            # t0 = 0x1000
        addi t0, t0, 0x41         # t0 = 0x1041
        and t2, a7, t0
        beq t2, t0, Win

        # 胜利条件5: 0x1110
        addi t0, zero, 0x11
        slli t0, t0, 8            # t0 = 0x1100
        addi t0, t0, 0x10         # t0 = 0x1110
        and t2, a7, t0
        beq t2, t0, Win

        # 胜利条件6: 0x10410
        addi t0, zero, 0x10
        slli t0, t0, 12           # t0 = 0x10000
        addi t0, t0, 0x410        # t0 = 0x10410
        and t2, a7, t0
        beq t2, t0, Win

        # 胜利条件7: 0x10101
        addi t0, zero, 0x10
        slli t0, t0, 12           # t0 = 0x10000
        addi t0, t0, 0x101        # t0 = 0x10101
        and t2, a7, t0
        beq t2, t0, Win

        j end_check


red_turn_check:
    # 胜利条件1: 0xa80
       addi t0, zero, 0xa8
       slli t0, t0, 4            # t0 = 0xa80
       and t2, a7, t0
       beq t2, t0, Win

       # 胜利条件2: 0x8208
       addi t0, zero, 0x82
       slli t0, t0, 8            # t0 = 0x8200
       addi t0, t0, 0x8          # t0 = 0x8208
       and t2, a7, t0
       beq t2, t0, Win

       # 胜利条件3: 0x2082
       addi t0, zero, 0x20
       slli t0, t0, 8            # t0 = 0x2000
       addi t0, t0, 0x82         # t0 = 0x2082
       and t2, a7, t0
       beq t2, t0, Win

       # 胜利条件4: 0x2220
       addi t0, zero, 0x22
       slli t0, t0, 8            # t0 = 0x2200
       addi t0, t0, 0x20         # t0 = 0x2220
       and t2, a7, t0
       beq t2, t0, Win

       # 胜利条件5: 0x20820
       addi t0, zero, 0x22
       slli t0, t0, 8            # t0 = 0x2200
       addi t0, t0, 0x20         # t0 = 0x2220
       and t2, a7, t0
       beq t2, t0, Win

       # 胜利条件6: 0x20202
       addi t0, zero, 0x20
       slli t0, t0, 12           # t0 = 0x20000
       addi t0, t0, 0x202        # t0 = 0x20202
       and t2, a7, t0
       beq t2, t0, Win

       # 胜利条件7: 0x2a
       addi t0, zero, 0x2a       # t0 = 0x2a
       and t2, a7, t0
       beq t2, t0, Win

       j end_check




end_check:
    xori a1, a1, 1              ## 切换玩家：0<->1
    j end_interrupt

Win:
    ## 胜利处理逻辑
    ## 设置胜利标志，显示胜利消息等
    addi a2, a1, 1             ## a2 用于存储胜利标志
    addi s5, zero, 3
    addi a7, a2, 0
    ecall
    j end_interrupt

end_interrupt:
    ## 返回
    uret
