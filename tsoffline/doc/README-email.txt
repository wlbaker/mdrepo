
If you google "java ole outlook mail provider", you might find this very useful site:

https://javaee.github.io/javamail/ThirdPartyProducts

What we would really like to have is a Provider that spoke OLE to the desktop Outlook.  
Kinda nice that would be.  You may also find info on writing a powershell script to
for outlook automation.

See: https://msdn.microsoft.com/en-us/magazine/dn189202.aspx
https://blogs.msdn.microsoft.com/jmanning/2007/01/25/using-powershell-for-outlook-automation/
Also: https://stackoverflow.com/questions/1453723/create-outlook-email-draft-using-powershell

$olFolderDrafts = 16
$ol = New-Object -comObject Outlook.Application 
$ns = $ol.GetNameSpace("MAPI")

# call the save method yo dave the email in the drafts folder
$mail = $ol.CreateItem(0)
$null = $Mail.Recipients.Add("XXX@YYY.ZZZ")  
$Mail.Subject = "PS1 Script TestMail"  
$Mail.Body = "  Test Mail  "
$Mail.save()

# get it back from drafts and update the body
$drafts = $ns.GetDefaultFolder($olFolderDrafts)
$draft = $drafts.Items | where {$_.subject -eq 'PS1 Script TestMail'}
$draft.body += "`n foo bar"
$draft.save()

# send the message
#$draft.Send()
