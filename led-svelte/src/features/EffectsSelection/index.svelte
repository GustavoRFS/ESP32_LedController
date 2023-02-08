<script lang="ts">
  import Ripple from "@smui/ripple";
  import Paper, { Title, Subtitle } from "@smui/paper";
  import "./index.css";

  const effects = [
    { title: "Strobe", subtitle: "Pisca Pisca", message: "S" },
    {
      title: "Smooth",
      subtitle: "Troca as cores de forma suave",
      message: "s",
    },
    {
      title: "Flash",
      subtitle: "Pisca rapidamente a última cor selecionada",
      message: "F",
    },
    {
      title: "Fade monocolor",
      subtitle: "Pisca lentamente a última cor selecionada",
      message: "f",
    },
    { title: "Fade", subtitle: "Pisca lentamente algumas cores", message: "e" },
  ];

  const sendMessage = console.log;
</script>

<div
  style="display: flex;flex-wrap:wrap;justify-content:center;gap:40px;padding:70px 0"
>
  {#each effects as effect}
    <div
      on:click={() => sendMessage(effect.message)}
      use:Ripple={{ surface: true, color: "primary" }}
      class="effect-card"
    >
      <Paper class="card-paper">
        <Title>{effect.title}</Title>
        <Subtitle>{effect.subtitle}</Subtitle>
      </Paper>
    </div>
  {/each}
</div>
