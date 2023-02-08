<script lang="ts">
  import colorConvert from "color-convert";
  import Button from "@smui/button/src/Button.svelte";
  import { onMount } from "svelte";
  import ws from "../../services/webSocket";
  import { Label } from "@smui/common";
  import { Color, ColorPicker } from "color-picker-svelte";
  import type { Color as ColorRGB } from "../../shared/@types/Color";
  import colorStore from "../../shared/stores/colors";
  import "./index.css";

  let color = new Color(
    `#${colorConvert.rgb.hex(
      $colorStore.color.r,
      $colorStore.color.g,
      $colorStore.color.b
    )}`
  );

  let shouldSend = false;

  onMount(() => {
    ws.onMessage<ColorRGB>("color", (data) => {
      shouldSend = false;
      const colorRGB: ColorRGB = data;

      color = new Color(
        `#${colorConvert.rgb.hex(colorRGB.r, colorRGB.g, colorRGB.b)}`
      );
    });
  });

  const handleColorSelection = () => {
    if (!shouldSend) {
      shouldSend = true;
      return;
    }

    const [r, g, b] = colorConvert.hex.rgb(color.toHexString());
    const message = {
      event: "color",
      data: { r, g, b },
    };

    colorStore.update((state) => ({ ...state, color: { r, g, b } }));

    ws.send(message);
  };

  const addToFavorites = () => {
    if (!color) return;

    const [r, g, b] = colorConvert.hex.rgb(color.toHexString());

    colorStore.update((state) => ({
      ...state,
      favorites: [...state.favorites, { type: "color", value: { r, g, b } }],
    }));
  };
</script>

<div
  style="display: flex;justify-content:center;flex-direction:column;align-items:center"
>
  <ColorPicker bind:color isOpen={true} onInput={handleColorSelection} />
  <p>
    <Button on:click={addToFavorites} variant="raised"
      ><Label>Adicionar cor aos favoritos</Label></Button
    >
  </p>
  <p>
    <Button variant="raised"><Label>-</Label></Button>
    Brilho
    <Button variant="raised"><Label>+</Label></Button>
  </p>
  <p>
    <Button variant="raised"><Label>-</Label></Button>
    Velocidade
    <Button variant="raised"><Label>+</Label></Button>
  </p>
</div>
