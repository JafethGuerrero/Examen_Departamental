const express = require('express');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());

let peatonDetectado = false;
let estadoCruce = "verde";
let tiempoRestante = 0;
let override = false;

app.get('/status', (req, res) => {
    res.json({
        peaton_detectado: peatonDetectado,
        estado_cruce: estadoCruce,
        tiempo_restante: tiempoRestante
    });
});

app.post('/manual_override', (req, res) => {
    override = req.body.forzar_cruce;
    if (override) {
        peatonDetectado = true;
        estadoCruce = "rojo";
        tiempoRestante = 10;
        res.json({ success: true, message: "Cruce forzado." });
    } else {
        res.json({ success: false, message: "No se forzó cruce." });
    }
});

// Simula el comportamiento automáticamente
setInterval(() => {
    if (peatonDetectado || override) {
        estadoCruce = "rojo";
        if (tiempoRestante > 0) {
            tiempoRestante--;
        } else {
            peatonDetectado = false;
            override = false;
            estadoCruce = "verde";
            tiempoRestante = 0;
        }
    }
}, 1000); // cada 1 segundo

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Servidor API escuchando en http://localhost:${PORT}`);
});
