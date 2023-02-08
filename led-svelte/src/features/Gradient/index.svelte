<script lang="ts">
  import { Color, ColorPicker } from "color-picker-svelte";
  import ws from "../../services/webSocket";
  import convert from "color-convert";
  import GradientMaker from "../../shared/components/GradientMaker/index.svelte";
  import type { Gradient } from "../../shared/@types/Color";
  import Button from "@smui/button/src/Button.svelte";
  import "./index.css";
  import colorStore from "../../shared/stores/colors";

  let currentGradientIndex = 0;

  let gradientColors: Gradient[] = [];

  colorStore.subscribe((state) => {
    gradientColors = state.gradient;
  });

  let color = new Color(
    convert.rgb.hex(
      gradientColors[currentGradientIndex].color.r,
      gradientColors[currentGradientIndex].color.g,
      gradientColors[currentGradientIndex].color.b
    )
  );

  const handleColorSelection = () => {
    const [r, g, b] = convert.hex.rgb(color.toHexString());

    gradientColors[currentGradientIndex].color = { r, g, b };

    onChange();
  };

  let shouldSend = false;

  const onChange = () => {
    if (!shouldSend) {
      shouldSend = true;
      return;
    }
    ws.send({
      event: "gradient",
      data: [...gradientColors].sort((a, b) => a.percentage - b.percentage),
    });
  };

  const onSelectGradientPoint = (index: number) => {
    currentGradientIndex = index;
    color = new Color(
      convert.rgb.hex(
        gradientColors[currentGradientIndex].color.r,
        gradientColors[currentGradientIndex].color.g,
        gradientColors[currentGradientIndex].color.b
      )
    );
  };

  const onClickAdd = () => {
    if (gradientColors.length === 10) return;

    const percentage = Math.random() * 100;
    colorStore.update((state) => ({
      ...state,
      gradient: [
        ...state.gradient,
        {
          color: {
            r: Math.random() * 255,
            g: Math.random() * 255,
            b: Math.random() * 255,
          },
          percentage,
        },
      ],
    }));

    currentGradientIndex = gradientColors.length - 1;
  };

  const addToFavorites = () => {
    colorStore.update((state) => ({
      ...state,
      favorites: [
        ...state.favorites,
        {
          type: "gradient",
          value: [...gradientColors].sort(
            (a, b) => a.percentage - b.percentage
          ),
        },
      ],
    }));
  };
</script>

<div class="container">
  <ColorPicker
    bind:color
    isOpen={true}
    onInput={handleColorSelection}
  /><GradientMaker
    {onChange}
    {gradientColors}
    {onSelectGradientPoint}
    {onClickAdd}
  />
  <div class="buttons">
    <Button on:click={addToFavorites} variant="raised"
      >Adicionar aos favoritos</Button
    >
  </div>
</div>
