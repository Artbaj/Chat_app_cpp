# --- USTAWIENIA ---
$exe = "ChatClient.exe"
$ip = "10.100.7.46" 
$totalBots = 200   
$delayBetween = 100
# ------------------

Write-Host "[!!!] URUCHAMIANIE $totalBots BOTOW [!!!]" -ForegroundColor Red

# Sprawdzenie czy plik exe istnieje (częsty powód zamykania okna)
if (-not (Test-Path $exe)) {
    Write-Host "BLAD: Nie znaleziono pliku $exe w folderze: $(Get-Location)" -ForegroundColor Red
    Write-Host "Nacisnij ENTER aby zamknac..."
    Read-Host
    exit
}

$tempFiles = @()

for ($i = 1; $i -le $totalBots; $i++) {
    $file = "bot_$i.txt"
    $name = "NuklearnyBot_$i"
    $tempFiles += $file

    # Generowanie instrukcji
    $commands = @($ip, $name, "1","9")
    $commands | Out-File -FilePath $file -Encoding ascii

    # Odpalanie
    Start-Process -FilePath $exe -RedirectStandardInput $file -WindowStyle Hidden
    
    Start-Sleep -Milliseconds $delayBetween

    if ($i % 50 -eq 0) {
        Write-Host "[+] Wypuszczono $i botow..." -ForegroundColor Yellow
    }
}

Write-Host "[OK] Wszystkie botyGOTOWE" -ForegroundColor Green
Write-Host "[INFO] Pliki konfiguracyjne (.txt) zostaną usunięte za 900kund..." -ForegroundColor Gray
Start-Sleep -Seconds 900

# Sprzątanie
foreach ($f in $tempFiles) {
    if (Test-Path $f) { Remove-Item $f }
}
Write-Host "[CLEAN] Posprzątano pliki tymczasowe." -ForegroundColor Cyan

# --- ZATRZYMANIE OKNA ---
Write-Host "`n---------------------------------------------------"
Write-Host "SKRYPT ZAKONCZYL PRACE (ale boty dzialaja w tle)." -ForegroundColor Green
Write-Host "Nacisnij ENTER, aby zamknac to okno..." -ForegroundColor White
Write-Host "---------------------------------------------------"


$null = Read-Host