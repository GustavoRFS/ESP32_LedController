<script lang="ts">
  import "./index.css";
  import GradientPoint from "../GradientPoint/index.svelte";
  import type { Color, Gradient } from "../../../shared/@types/Color";
  import { onMount, beforeUpdate } from "svelte";

  export let gradientColors: Gradient[];
  export let onSelectGradientPoint: (index: number) => void;
  export let onClickAdd: () => void;
  export let onChange: (() => void) | undefined;

  let linearGradientStyle = "";

  const add = () => {
    onClickAdd();
    onChange();
  };

  const updateGradientDisplay = () => {
    linearGradientStyle = "background: linear-gradient(90deg";

    const arrayCopy = [...gradientColors];
    arrayCopy
      .sort((c1, c2) => c1.percentage - c2.percentage)
      .forEach(({ color, percentage }) => {
        linearGradientStyle += `,rgb(${color.r},${color.g},${color.b}) ${percentage}%`;
      });
    linearGradientStyle += ")";
  };

  onMount(() => updateGradientDisplay());

  beforeUpdate(() => {
    updateGradientDisplay();
  });
</script>

<div>
  <div class="gradient-maker-container">
    <div class="gradient-maker" style={linearGradientStyle}>
      {#each gradientColors as gradientColor, index}
        {#key index}
          <GradientPoint
            percentage={gradientColor.percentage}
            color={gradientColor.color}
            onMove={(percentage) => {
              gradientColor.percentage = percentage;
              updateGradientDisplay();
              onChange();
            }}
            onClick={() => onSelectGradientPoint(index)}
          />
        {/key}
      {/each}
    </div>
    <button on:click={add} class="add-point-button">+</button>
  </div>
</div>
