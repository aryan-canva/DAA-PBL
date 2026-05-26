
import React, { useState } from "react";

export default function App() {

    const [budget, setBudget] = useState(200);

    const [diet, setDiet] = useState("veg");

    const [allergens, setAllergens] = useState([]);

    const [result, setResult] = useState("");

    const [loading, setLoading] = useState(false);

    function handleAllergen(e) {

        const value = e.target.value;

        if (e.target.checked) {

            setAllergens([
                ...allergens,
                value
            ]);

        } else {

            setAllergens(
                allergens.filter(
                    (a) => a !== value
                )
            );
        }
    }

    async function generateMeal() {

        setLoading(true);

        setResult(
            "Generating meal plan..."
        );

        try {

            const response = await fetch(
                "http://localhost:5000/generate",
                {
                    method: "POST",

                    headers: {
                        "Content-Type":
                            "application/json"
                    },

                    body: JSON.stringify({
                        budget:
                            Number(budget),

                        diet: diet,

                        allergens:
                            allergens.join(",")
                    })
                }
            );

            const data =
                await response.json();

            console.log(data);

            if (data.output) {

                setResult("");

                setTimeout(() => {

                    setResult(
                        data.output
                    );

                }, 50);

            } else {

                setResult(
                    data.error ||
                    "No output received."
                );
            }

        } catch (err) {

            console.log(err);

            setResult(
                "Backend connection failed."
            );
        }

        setLoading(false);
    }

    return (

        <div
            style={{
                minHeight: "100vh",
                background:
                    "#f3f4f6",
                display: "flex",
                justifyContent:
                    "center",
                alignItems:
                    "center",
                padding: "30px"
            }}
        >

            <div
                style={{
                    background: "white",
                    width: "700px",
                    padding: "30px",
                    borderRadius: "20px",
                    boxShadow:
                        "0 0 20px rgba(0,0,0,0.1)"
                }}
            >

                <h1
                    style={{
                        textAlign:
                            "center",
                        marginBottom:
                            "25px"
                    }}
                >
                    Budget Meal Planner
                </h1>

                <label>
                    Budget (Rs)
                </label>

                <input
                    type="number"
                    value={budget}
                    onChange={(e) =>
                        setBudget(
                            e.target.value
                        )
                    }
                    style={{
                        width: "100%",
                        padding: "12px",
                        marginTop: "8px",
                        marginBottom:
                            "20px"
                    }}
                />

                <label>
                    Diet Type
                </label>

                <select
                    value={diet}
                    onChange={(e) =>
                        setDiet(
                            e.target.value
                        )
                    }
                    style={{
                        width: "100%",
                        padding: "12px",
                        marginTop: "8px",
                        marginBottom:
                            "20px"
                    }}
                >

                    <option value="veg">
                        Veg
                    </option>

                    <option value="non-veg">
                        Non-Veg
                    </option>

                    <option value="lactose-free">
                        Lactose-Free
                    </option>

                    <option value="any">
                        Any
                    </option>

                </select>

                <h3>
                    Allergens to Avoid
                </h3>

                <div
                    style={{
                        marginBottom:
                            "25px"
                    }}
                >

                    <label>
                        <input
                            type="checkbox"
                            value="milk"
                            onChange={
                                handleAllergen
                            }
                        />
                        Milk
                    </label>

                    <br />

                    <label>
                        <input
                            type="checkbox"
                            value="peanut"
                            onChange={
                                handleAllergen
                            }
                        />
                        Peanut
                    </label>

                    <br />

                    <label>
                        <input
                            type="checkbox"
                            value="soy"
                            onChange={
                                handleAllergen
                            }
                        />
                        Soy
                    </label>

                    <br />

                    <label>
                        <input
                            type="checkbox"
                            value="gluten"
                            onChange={
                                handleAllergen
                            }
                        />
                        Gluten
                    </label>

                </div>

                <button
                    onClick={
                        generateMeal
                    }
                    style={{
                        width: "100%",
                        padding: "14px",
                        background:
                            "black",
                        color: "white",
                        border: "none",
                        borderRadius:
                            "10px",
                        fontSize: "16px",
                        cursor: "pointer"
                    }}
                >

                    {
                        loading
                        ? "Generating..."
                        : "Generate Meal Plan"
                    }

                </button>

                <pre
                    style={{
                        marginTop: "25px",
                        background:
                            "#eeeeee",
                        padding: "20px",
                        borderRadius:
                            "12px",
                        whiteSpace:
                            "pre-wrap",
                        overflowX:
                            "auto"
                    }}
                >

                    {
                        result ||
                        "Meal plan output will appear here."
                    }

                </pre>

            </div>

        </div>
    );
}