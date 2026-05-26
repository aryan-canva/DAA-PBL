
const express = require("express");

const cors = require("cors");

const { exec } = require("child_process");

const path = require("path");

const app = express();

app.use(cors());

app.use(express.json());

app.post("/generate", (req, res) => {

    const {
        budget,
        diet,
        allergens
    } = req.body;

    const executablePath =
        path.join(
            __dirname,
            "../backend/mealplanner"
        );

    const command =
        `${executablePath} ${budget} ${diet} "${allergens}" ${Date.now()}`;

    console.log(command);

    exec(command, (error, stdout, stderr) => {

        if (error) {

            console.log(stderr);

            return res.status(500).json({
                error:
                    stderr ||
                    error.message
            });
        }

        res.json({
            output: stdout
        });
    });
});

app.listen(5000, () => {

    console.log(
        "Server running on port 5000"
    );
});