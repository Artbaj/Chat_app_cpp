# --- USTAWIENIA ---

$exe = "ChatClient.exe"

$ip = "10.100.7.46" # Zmieniłem na localhost dla bezpieczeństwa przykładu

$totalBots = 60   # Ustaw na 600 jeśli jesteś gotowy :)

$delayBetween = 1000 # ms (zwiększyłem lekko dla stabilności OS)

# ------------------



Write-Host "[!!!] URUCHAMIANIE $totalBots BOTOW [!!!]" -ForegroundColor Red



# Lista stworzonych plików tymczasowych do późniejszego usunięcia

$tempFiles = @()



for ($i = 1; $i -le $totalBots; $i++) {

    $file = "bot_$i.txt"

    $name = "NuklearnyBot_$i"

    

    # Dodajemy plik do listy do posprzątania

    $tempFiles += $file



    # Generowanie instrukcji

    # Upewnij się, że ostatnia linia w C++ pozwala na "wiszenie" klienta, 

    # albo że klient nie zamyka się natychmiast po wysłaniu wiadomości (chyba że tego chcesz).

    $commands = @($ip, $name, "1","9")

    $commands | Out-File -FilePath $file -Encoding ascii



    # Odpalanie w tle

    # PassThru zwraca obiekt procesu, co pozwalałoby nam je śledzić, ale tu wystarczy Hidden

    Start-Process -FilePath $exe -RedirectStandardInput $file -WindowStyle Hidden

    

    # --- FIX: Użycie opóźnienia ---

    Start-Sleep -Milliseconds $delayBetween



    if ($i % 50 -eq 0) {

        Write-Host "[+] Wypuszczono $i botow..." -ForegroundColor Yellow

    }

}



Write-Host "[OK] Wszystkie boty w natarciu." -ForegroundColor Green

Write-Host "[INFO] Pliki konfiguracyjne (.txt) zostaną usunięte za 5 sekund..." -ForegroundColor Gray

Start-Sleep -Seconds 5



# --- FIX: Sprzątanie ---

foreach ($f in $tempFiles) {

    if (Test-Path $f) { Remove-Item $f }

}

Write-Host "[CLEAN] Posprzątano pliki tymczasowe." -ForegroundColor Cyan