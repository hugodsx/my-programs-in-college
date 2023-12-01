<meta charset="utf-8">

<%@ Language="VBScript" CodePage =65001 %>
<%

On Error Resume Next

dim Username, Heure, Score, Realtime
Heure = Request.Form("TIME")
Score = Request.Form("SCORE")
Username = Request.Form("username")
Realtime = Request.Form("REALTIME")

DBpath = "C:\inetpub\wwwroot\experiment3\score111.mdb"
Set conn = Server.CreateObject("ADODB.Connection")
Set rs = Server.CreateObject("ADODB.Recordset")
conn.Open "driver={Microsoft Access Driver (*.mdb)}; dbq=" & DBpath
rs.Open "score", conn, adOpenDynamic, 2

rs.AddNew
rs("s_name") = Username
rs("s_score") = Score
rs("s_time") = Heure
rs("s_realtime") = Realtime
rs.Update

rs.Close()
conn.Close()
Response.Write "<html><body><center><font size=5px>成绩已上传！<p>"
Response.Write "<html><body><center><font size=4px>排名<p>"
Server.Execute("scoredisplay.asp")

If Err.Number <> 0 Then
Response.Write "Error: " & Err.Description
Err.Clear
End If
On Error GoTo 0

%>
