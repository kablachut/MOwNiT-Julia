
Pkg.add("FFTW")
using Plots
using FFTW



Fs = 1024

t = 0:1/(Fs-1):1;

x = sin.(2*pi*t*200) + 2* sin.(2*pi*t*400)

plot(t,x)



sticks((abs.(fft(x))))

function cutFifty(x)
    if x < 50
        return 0
    else
        return x
    end
end

Fs = 1024

t = 0:1/(Fs-1):1;

x = cos.(4*pi*t*200)

data = [cos.(4*pi*t*200) * rand() for t in 0:1/(Fs-1):1]

plot(data)

spectrum = (abs.(fft(data)))

sticks(abs.(fft(data)))



#spectrum after filtering
spectrum = map(cutFifty, spectrum)


ispectrum = (abs.(ifft(spectrum)))

sticks(real.(ispectrum))
        
#compared with original data
sticks!(-abs.(data), color="red")

Pkg.add("WAV")
using WAV

snd, sampFreq = wavread("voice.wav")


function cutFreq(spectrum, a, b)
    for x in 1:length(spectrum)
        if x >= a && x <= b
            spectrum[x] = 0
        end
end
end



s1 = snd[:,1]

plot(s1)

spectrum = imag.(fft(s1)) + real.(fft(s1))

#sticks(real(spectrum))


cutFreq(spectrum, 0, 10000)
cutFreq(spectrum, 215000, 500000)

cutFreq(spectrum, 50000, 175000)

sticks!(real(spectrum))

plot(s1)
plot!(reverse(imag.(ifft(spectrum)) + real.(ifft(spectrum))))



wavwrite(reverse(imag.(ifft(spectrum)) + real.(ifft(spectrum))), "converted_voice.wav", Fs=44000)
