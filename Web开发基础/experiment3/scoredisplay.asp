<meta charset="utf-8">
<%@ Language="VBScript" CodePage="65001" %>

<%
On Error Resume Next

Dim conn, connStr, rs
Set conn = Server.CreateObject("ADODB.Connection")
connStr = "driver={Microsoft Access Driver (*.mdb)}; dbq=C:\inetpub\wwwroot\experiment3\score111.mdb;"
conn.Open connStr

If Err <> 0 Then
    Response.Write "数据库连接失败！"
    Response.End
End If

Dim sqlText
sqlText = "SELECT s_name, s_score, s_time FROM score ORDER BY s_score DESC, s_realtime ASC"
Set rs = Server.CreateObject("ADODB.Recordset")
rs.Open sqlText, conn

While Not rs.EOF
    Response.Write "姓名: " & rs("s_name") & "<br>"
    Response.Write "分数: " & rs("s_score") & "<br>"
    Response.Write "时间: " & rs("s_time") & "<br><br>"
    
    rs.MoveNext
Wend

rs.Close
Set rs = Nothing
conn.Close
Set conn = Nothing

If Err.Number <> 0 Then
Response.Write "Error: " & Err.Description
Err.Clear
End If
On Error GoTo 0
%>
