scriptPath := A_ScriptDir "\run_auto_clicker.vbs"

; Alt + F12 to trigger the script
!F12::
    ; Check if the script is already running as admin
    if not A_IsAdmin
    {
        ; If not running as admin, restart the script as admin
        Run *RunAs "%A_ScriptFullPath%"
        ExitApp
    }
    ; If running as admin, run the specified script
    Run, %scriptPath%
return
