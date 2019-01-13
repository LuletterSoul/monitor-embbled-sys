VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "示例2-控制器"
   ClientHeight    =   5040
   ClientLeft      =   6060
   ClientTop       =   2445
   ClientWidth     =   9900
   LinkTopic       =   "Form1"
   ScaleHeight     =   5040
   ScaleWidth      =   9900
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
      Height          =   3855
      Left            =   0
      TabIndex        =   0
      Top             =   360
      Width           =   9735
      Begin VB.TextBox Text5 
         Height          =   495
         Left            =   6360
         TabIndex        =   14
         Text            =   "分"
         Top             =   600
         Width           =   975
      End
      Begin VB.TextBox Text4 
         Height          =   495
         Left            =   7560
         TabIndex        =   13
         Text            =   "秒"
         Top             =   600
         Width           =   975
      End
      Begin VB.CommandButton Command5 
         Caption         =   "过10秒启动"
         Height          =   495
         Left            =   4920
         TabIndex        =   12
         Top             =   600
         Width           =   1215
      End
      Begin VB.TextBox Text3 
         Height          =   495
         Left            =   2640
         TabIndex        =   11
         Top             =   600
         Width           =   1575
      End
      Begin VB.TextBox Text2 
         Height          =   495
         Left            =   360
         TabIndex        =   10
         Top             =   600
         Width           =   1575
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
         Top             =   1440
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
         Top             =   1440
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
         Top             =   2760
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
         Top             =   2760
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
         Top             =   1440
         Width           =   1815
      End
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   0
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
Dim s As Integer, m As Integer, h As Integer


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
    Command5.Enabled = True
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
    Command5.Enabled = False
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
    Command5.Enabled = False
End Sub

Private Sub Command4_Click()
    End
End Sub

Private Sub Command5_Click()
    Dim res As Integer:
        res = &H0
    Dim t As Date:
        t = Now
    Dim s1(0) As Byte:
    s1(0) = &H30
    res = res + s1(0)
    Form1.MSComm1.Output = s1
    s1(0) = &H36              '发10秒启动命令
    res = res + s1(0)
    Form1.MSComm1.Output = s1
    Dim int1 As Byte
    int1 = (Minute(t) \ 10) * 16 + (Minute(t) Mod 10)
    'MsgBox Minute(t)
    s1(0) = int1
     res = res + s1(0)
    Form1.MSComm1.Output = s1
     Dim int2 As Byte
    int2 = (Second(t) \ 10) * 16 + (Second(t) Mod 10)
     'MsgBox Second(t)
    s1(0) = int2
    res = res + s1(0)
    Form1.MSComm1.Output = s1
     s1(0) = &H0
    Form1.MSComm1.Output = s1
    '计算校验码
    res = res Mod 256
    s1(0) = (res \ 16) * 2 ^ 4 Or res Mod 16
    'MsgBox s1(0)
    Form1.MSComm1.Output = s1
    
    Command5.Enabled = False
    Command2.Enabled = True
    Command1.Enabled = False
    Command3.Enabled = False
    Frame1.Enabled = False
End Sub

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
    res = res Mod 256
    s1(0) = (res \ 16) * 2 ^ 4 Or res Mod 16
    'MsgBox s1(0)
    Form1.MSComm1.Output = s1
End Sub







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
    Text2 = ""
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
                        Text2 = "电机启动成功"
                    End If
                    If RevByte(2) = &H21 Then
                        Text2 = "电机停止成功"
                    End If
                    If RevByte(2) = &H31 Then
                        Text2 = "电机加速成功" & "当前占空比为:" & RevByte(3)
                        Text1 = RevByte(3)
                    End If
                    If RevByte(2) = &H41 Then
                        Text2 = "电机减速成功" & "当前占空比为:" & RevByte(3)
                        Text1 = RevByte(3)
                    End If
                    If RevByte(2) = &H51 Then
                        Text2 = "电机进入调速模式" & "当前占空比为:" & RevByte(3)
                        Text1 = RevByte(3)
                    End If
                    If RevByte(2) = &H61 Then
                        Text2 = "电机进入定时启动模式成功"
                    End If
                   'Text2 = "电机方校验成功"
                   ' If RevByte(2) = &O1 Then '显示占空比'
                   '     Text1 = RevByte(3)
                   ' End If
                End If
                If RevByte(1) = &H2 Then
                    If RevByte(2) = &H12 Then
                        Text2 = "电机启动失败"
                    End If
                    If RevByte(2) = &H22 Then
                        Text2 = "电机停止失败"
                    End If
                    If RevByte(2) = &H32 Then
                        Text2 = "电机加速失败"
                    End If
                    If RevByte(2) = &H42 Then
                        Text2 = "电机减速失败"
                    End If
                    If RevByte(2) = &H52 Then
                        Text2 = "电机进入调速模式失败"
                    End If
                    If RevByte(2) = &H62 Then
                        Text2 = "电机进入定时启动模式失败"
                    End If
                End If
                If RevByte(1) = &H3 Then
                    Text2 = "主机发送了未知的指令"

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
    End If
End Sub

