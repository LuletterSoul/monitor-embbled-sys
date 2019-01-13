VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "示例2-控制器"
   ClientHeight    =   9045
   ClientLeft      =   6060
   ClientTop       =   2445
   ClientWidth     =   10605
   LinkTopic       =   "Form1"
   ScaleHeight     =   9045
   ScaleWidth      =   10605
   Begin VB.Frame Frame2 
      Caption         =   "远程操控"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   21.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   7935
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   9735
      Begin VB.CommandButton Command7 
         Caption         =   "发送未知指令"
         Height          =   855
         Left            =   4920
         TabIndex        =   14
         Top             =   3840
         Width           =   1695
      End
      Begin VB.CommandButton Command6 
         Caption         =   "电机调速测试"
         Height          =   855
         Left            =   2640
         TabIndex        =   13
         Top             =   3840
         Width           =   1695
      End
      Begin VB.CommandButton Command5 
         Caption         =   "电机启动/停止测试"
         Height          =   855
         Left            =   360
         TabIndex        =   12
         Top             =   3840
         Width           =   1695
      End
      Begin VB.TextBox Text3 
         Height          =   495
         Left            =   6960
         TabIndex        =   11
         Top             =   480
         Width           =   2055
      End
      Begin VB.TextBox Text2 
         Height          =   2055
         Left            =   240
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   10
         Top             =   5160
         Width           =   8895
      End
      Begin VB.Frame Frame1 
         Caption         =   "通过滚动条调速"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   15.75
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2175
         Left            =   4680
         TabIndex        =   5
         Top             =   1200
         Width           =   4935
         Begin VB.TextBox Text1 
            Height          =   375
            Left            =   2040
            TabIndex        =   9
            Text            =   "占空比"
            Top             =   840
            Width           =   975
         End
         Begin VB.HScrollBar HScroll1 
            Height          =   615
            LargeChange     =   2
            Left            =   240
            Max             =   30
            Min             =   4
            SmallChange     =   2
            TabIndex        =   6
            Top             =   1320
            Value           =   30
            Width           =   4455
         End
         Begin VB.Label Label2 
            Caption         =   "低速"
            BeginProperty Font 
               Name            =   "宋体"
               Size            =   12
               Charset         =   134
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   4080
            TabIndex        =   8
            Top             =   960
            Width           =   495
         End
         Begin VB.Label Label1 
            Caption         =   "高速"
            BeginProperty Font 
               Name            =   "宋体"
               Size            =   12
               Charset         =   134
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   480
            TabIndex        =   7
            Top             =   960
            Width           =   495
         End
      End
      Begin VB.CommandButton Command1 
         Caption         =   "调速"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   21.75
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   855
         Left            =   240
         TabIndex        =   4
         Top             =   960
         Width           =   1815
      End
      Begin VB.CommandButton Command4 
         Caption         =   "退出"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   21.75
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   855
         Left            =   2520
         TabIndex        =   3
         Top             =   2520
         Width           =   1815
      End
      Begin VB.CommandButton Command3 
         Caption         =   "启动"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   21.75
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   855
         Left            =   240
         TabIndex        =   2
         Top             =   2520
         Width           =   1815
      End
      Begin VB.CommandButton Command2 
         Caption         =   "停止"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   21.75
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   855
         Left            =   2520
         TabIndex        =   1
         Top             =   960
         Width           =   1815
      End
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   240
      Top             =   4200
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      BaudRate        =   115200
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim r As Integer
Dim S As Integer, m As Integer, h As Integer


Private Declare Function timeGetTime Lib "winmm.dll" () As Long

Private Sub Command2_Click()
    Dim s1(0) As Byte:
    s1(0) = &H30
    Form1.MSComm1.Output = s1
    s1(0) = &H32     '发停止命令
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H62
    Form1.MSComm1.Output = s1
    Frame1.Enabled = False
    Command1.Enabled = True
    Command3.Enabled = True
    Command2.Enabled = False
End Sub
Private Sub Command1_Click()
  Dim s1(0) As Byte:
    s1(0) = &H30
    Form1.MSComm1.Output = s1
    s1(0) = &H33    '发调速命令
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H63
    Form1.MSComm1.Output = s1
    Frame1.Enabled = True
    Command2.Enabled = True
    Command1.Enabled = False
    Command3.Enabled = False
End Sub

Private Sub Command3_Click()
   Dim s1(0) As Byte:
     s1(0) = &H30
    Form1.MSComm1.Output = s1
    s1(0) = &H31              '发启动命令
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
     s1(0) = &H61
    Form1.MSComm1.Output = s1
    Command2.Enabled = True
    Command1.Enabled = False
    Command3.Enabled = False
End Sub

Private Sub Command4_Click()
    End
End Sub

'Suite1 : 测试电机启动/停止
Private Sub Command5_Click()
    b = sendPkt(&H30, &H31, &H0, &H0, &H0, &H61) '发送启动电机指令,使得校验和对,期待结果为电机启动'
    Sleep (5000)
    
    b = sendPkt(&H30, &H32, &H0, &H0, &H0, &H62) '发送停止电机指令,使得校验和对,期待结果为电机停止'
    Sleep (5000)
    
    b = sendPkt(&H30, &H31, &H0, &H0, &H0, &H42) '发送启动电机指令,使得校验和错,期待结果为电机反馈启动失败信息'
    Sleep (5000)
    
    b = sendPkt(&H30, &H31, &H0, &H0, &H0, &H61) '发送启动电机指令,使得校验和对,期待结果为电机启动'
    Sleep (5000)
    
    b = sendPkt(&H30, &H32, &H0, &H0, &H0, &H61) '发送停止电机指令,使得校验和错,期待结果为电机反馈停止失败信息'
    Sleep (5000)
    
    b = sendPkt(&H30, &H32, &H0, &H0, &H0, &H62) '发送停止电机指令,使得校验和对,期待结果为电机停止'
End Sub

'Suite2: 测试电机的调速模式
Private Sub Command6_Click()
    Dim i As Integer
    Dim ration As Integer
    Dim lowSum As Byte
    Dim rb As Byte
    ration = 10
    i = 0
    Sleep (2000)
    b = sendPkt(&H30, &H33, &H0, &H0, &H0, &H63) '发送调速指令,使得校验和对,,期待结果为电机进入调速模式并反馈'
    Sleep (2000)
    '占空比从10增加到30,期待结果为:电机从快到慢转动
    For i = 0 To 10
        rb = (ration \ 10) * 16 + (ration Mod 10)
        lowSum = calSum(&H30, &H33, rb, &H0)
        b = sendPkt(&H30, &H33, rb, &H0, &H0, lowSum)
        Sleep (2000) '每隔2s减速一次
        ration = ration + 2
    Next
    
    '占空比从30递减到10,期待结果为:电机从慢到快转动
    ration = 30
    For i = 0 To 10
        rb = (ration \ 10) * 16 + (ration Mod 10)
        lowSum = calSum(&H30, &H33, rb, &H0)
        b = sendPkt(&H30, &H33, rb, &H0, &H0, lowSum)
        Sleep (2000) '每隔2s加速一次
        ration = ration - 2
    Next
    
    
    b = sendPkt(&H30, &H32, &H0, &H0, &H0, &H62) '退出调试模式'
    rb = (ration \ 10) * 16 + (ration Mod 10)
    lowSum = calSum(&H30, &H33, rb, &H0)
    
    Sleep (2000)
    b = sendPkt(&H30, &H33, &H0, &H0, &H0, &H65) '发送调速指令,使得校验和错,,期待结果为电机未进入调速模式并反馈'
    
    '未成功进入调速模式,发送了加速命令
    Sleep (2000)
    b = sendPkt(&H30, &H0, rb, &H0, &H0, lowSum)  '发送不带调速FLAG的加速指令,期待结果为电机调速错误，当前不处于调速模式'
    Sleep (2000)
    b = sendPkt(&H30, &H33, rb, &H0, &H0, lowSum)  '发送带调速FLAG的加速指令,期待结果为电机调进入速模式调速成功'
    Sleep (2000)
    '占空比从30递减到10,期待结果为:电机从慢到快转动
    ration = 30
    For i = 0 To 10
        rb = (ration \ 10) * 16 + (ration Mod 10)
        lowSum = calSum(&H30, &H33, rb, &H0)
        b = sendPkt(&H30, &H33, rb, &H0, &H0, lowSum)
        Sleep (2000) '每隔2s加速一次
        ration = ration - 2
    Next
    
End Sub

'发送指
Private Sub Command7_Click()
    
End Sub


Public Function Sleep(time As Double)
    Dim SaveTime As Double
    SaveTime = timeGetTime
    While timeGetTime < SaveTime + time
    DoEvents 'dede'
    Wend
End Function


Public Function sendPkt(b0 As Byte, b1 As Byte, b2 As Byte, b3 As Byte, b4 As Byte, b5 As Byte)
    Dim b(0) As Byte
    b(0) = b0
    Form1.MSComm1.Output = b
    b(0) = b1
    Form1.MSComm1.Output = b
    b(0) = b2
    Form1.MSComm1.Output = b
    b(0) = b3
    Form1.MSComm1.Output = b
    b(0) = b4
    Form1.MSComm1.Output = b
    b(0) = b5
    Form1.MSComm1.Output = b
    'Text2 = Hex(b0) & " " & Hex(b1) & " " & Hex(b2) & " " & Hex(b3) & " " & Hex(b4) & " " & Hex(b5)
End Function





Private Sub Form_Load()
    '判断串口1是否打开,若未打开则打开串口
    If Not Form1.MSComm1.PortOpen Then
       Form1.MSComm1.PortOpen = True
       Form1.MSComm1.DTREnable = True
       Form1.MSComm1.RTSEnable = True
    End If
    Me.KeyPreview = True
    Form1.MSComm1.RThreshold = 7                  '每接受7个字符就触发一次Read事件
    Form1.MSComm1.InputLen = 7                    '一次读7个字符
    Form1.MSComm1.InputMode = comInputModeBinary  '接收模式是二进制
    
    
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    Select Case KeyCode
        Case vbKeyA: Dim s1(0) As Byte:
                    s1(0) = &H30
                    Form1.MSComm1.Output = s1
                    s1(0) = &H34                '发加速命令
                    Form1.MSComm1.Output = s1
                     s1(0) = &H0
                    Form1.MSComm1.Output = s1
                     s1(0) = &H0
                    Form1.MSComm1.Output = s1
                     s1(0) = &H0
                    Form1.MSComm1.Output = s1
                     s1(0) = &H64
                    Form1.MSComm1.Output = s1
        Case vbKeyD: Dim s2(0) As Byte:
                    s2(0) = &H30
                    Form1.MSComm1.Output = s2
                    s2(0) = &H35                '发减速命令
                    Form1.MSComm1.Output = s2
                    s2(0) = &H0
                    Form1.MSComm1.Output = s2
                    s2(0) = &H0
                    Form1.MSComm1.Output = s2
                     s2(0) = &H0
                    Form1.MSComm1.Output = s2
                     s2(0) = &H65
                    Form1.MSComm1.Output = s2
                   
    End Select
    Frame1.Enabled = True
    Command1.Enabled = False
    Command2.Enabled = True
    Command3.Enabled = False
End Sub



Private Sub HScroll1_Change()
    Dim res As Integer:
    res = &H0
    Dim s1(0) As Byte:
    s1(0) = &H30
    res = res + s1(0)
    Form1.MSComm1.Output = s1
    s1(0) = &H33
     res = res + s1(0)
     Form1.MSComm1.Output = s1
    Dim int1 As Byte
    int1 = (HScroll1.Value \ 10) * 16 + (HScroll1.Value Mod 10)
    Text1 = HScroll1.Value
    s1(0) = int1
    res = res + s1(0)
    Form1.MSComm1.Output = s1
    s1(0) = &H0
     res = res + s1(0)
     Form1.MSComm1.Output = s1
    s1(0) = &H0
    Form1.MSComm1.Output = s1
    'MsgBox res
    s1(0) = (res \ 16) * 2 ^ 4 Or res Mod 16
    'MsgBox s1(0)
    Form1.MSComm1.Output = s1
End Sub


Public Function calSum(b0 As Byte, b1 As Byte, b2 As Byte, b3 As Byte)
    Dim sum As Integer
    sum = 0
    sum = b0 + b1 + b2 + b3
    calSum = (sum \ 16) * 2 ^ 4 Or sum Mod 16
End Function




Private Sub MSComm1_OnComm()
    'Dim Recebuf2 As Variant     '定义串口2的接收信息变量，变体类型
    'Dim temp As Integer
    'Dim c As Byte
    'Dim code As Integer:
    '     code = 0
    'temp = Form1.MSComm1.InBufferCount
    'If temp > 0 Then
    '    Recebuf2 = Form1.MSComm1.Input       'Recebuf2是公共变量
    '    byte1 = Recebuf2(0)
    '    code = Hex(byte1)
    '    If code = &H1 Then
    '        Text2 = "校验成功"
    '    End If
    '    If code = &H2 Then
    '        Text2 = "校验失败"
    '    End If
    'End If
    Dim RevByte As Variant
    Dim cnt As Integer
    cnt = Form1.MSComm1.InBufferCount
    Dim dt As Date
    dt = Now
    Dim strDate As String
    strDate = Format(dt, "yyyy年MM月dd日mm分ss秒")
    Text3 = ""
    If cnt > 0 Then
        RevByte = Form1.MSComm1.Input
        If RevByte(0) = &H30 And RevByte(6) = &H60 Then '判断起始符是否为协议要求的起始符'
            Dim sum As Integer
            Dim pktSum As Integer
            sum = 0
            sum = (RevByte(0) Mod 256) + (RevByte(1) Mod 256) + (RevByte(2) Mod 256) + (RevByte(3) Mod 256)
            pktSum = (RevByte(4) - &H30) * 10 + (RevByte(5) - &H30)
            If sum = pktSum Then '确保对方消息的可信度'
                Text3 = "收到的信息正确"
                If RevByte(1) = &H1 Then
                    If RevByte(2) = &H11 Then
                        Text2.Text = Text2.Text & "电机启动成功"
                    End If
                    If RevByte(2) = &H21 Then
                        Text2.Text = Text2.Text & "电机停止成功"
                    End If
                    If RevByte(2) = &H31 Then
                        Text2 = "电机加速成功" & "当前占空比为:" & RevByte(3)
                        Text1 = RevByte(3)
                    End If
                    If RevByte(2) = &H41 Then
                        Text2 = Text2.Text & "电机减速成功" & "当前占空比为:" & RevByte(3)
                        Text1 = RevByte(3)
                    End If
                    If RevByte(2) = &H51 Then
                        Text2 = Text2.Text & "电机进入调速模式" & "当前占空比为:" & RevByte(3)
                        Text1 = RevByte(3)
                    End If
                    If RevByte(2) = &H61 Then
                        Text2 = Text2.Text & "电机进入定时启动模式成功"
                    End If
                   'Text2 = "电机方校验成功"
                   ' If RevByte(2) = &O1 Then '显示占空比'
                   '     Text1 = RevByte(3)
                   ' End If
                End If
                If RevByte(1) = &H2 Then
                    If RevByte(2) = &H12 Then
                        Text2 = Text2.Text & "电机启动失败"
                    End If
                    If RevByte(2) = &H22 Then
                        Text2 = Text2.Text & "电机停止失败"
                    End If
                    If RevByte(2) = &H32 Then
                        Text2 = Text2.Text & "电机加速失败"
                    End If
                    If RevByte(2) = &H42 Then
                        Text2 = Text2.Text & "电机减速失败"
                    End If
                    If RevByte(2) = &H52 Then
                        Text2 = Text2.Text & "电机进入调速模式失败"
                    End If
                    If RevByte(2) = &H62 Then
                        Text2 = Text2.Text & "电机进入定时启动模式失败"
                    End If
                End If
                If RevByte(1) = &H3 Then
                    Text2 = Text2.Text & "主机发送了未知的指令"

                End If
                If RevByte(1) = &H4 Then
                    'Text2 = "收到RTC回馈"
                    Text4 = RevByte(3)
                    Text5 = RevByte(2)
                End If
                    
            Else
               Text3 = "收到的信息损坏"
         End If
        Else '如果起始符不是双方要求的起始符,则认为该帧不是合法的'
            Text2 = "起始符不正确"
            Text3 = "未知的帧"
            Text2 = RevByte(0) & " " & RevByte(1) & " " & RevByte(2) & " " & RevByte(3) & " " & RevByte(4) & " " & RevByte(5) & " " & RevByte(6)
        End If
        Text2.Text = Text2.Text & "                   " & strDate & vbCrLf
    End If
End Sub

